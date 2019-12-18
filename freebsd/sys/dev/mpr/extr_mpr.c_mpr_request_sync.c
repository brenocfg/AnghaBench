#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct mpr_softc {int dummy; } ;
struct TYPE_5__ {int td_pflags; scalar_t__ td_no_sleeping; } ;
struct TYPE_4__ {int MsgLength; } ;
typedef  TYPE_1__ MPI2_DEFAULT_REPLY ;

/* Variables and functions */
 int CAN_SLEEP ; 
 int EBUSY ; 
 int ENXIO ; 
 int MIN (int,int) ; 
 int MPI2_DOORBELL_ADD_DWORDS_SHIFT ; 
 int MPI2_DOORBELL_DATA_MASK ; 
 int MPI2_DOORBELL_FUNCTION_SHIFT ; 
 int /*<<< orphan*/  MPI2_DOORBELL_OFFSET ; 
 int MPI2_DOORBELL_USED ; 
 int MPI2_FUNCTION_HANDSHAKE ; 
 int /*<<< orphan*/  MPI2_HOST_INTERRUPT_STATUS_OFFSET ; 
 int /*<<< orphan*/  MPR_ERROR ; 
 int /*<<< orphan*/  MPR_FAULT ; 
 int NO_SLEEP ; 
 int TDP_NOSLEEPING ; 
 TYPE_3__* curthread ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int mpr_regread (struct mpr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_regwrite (struct mpr_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpr_wait_db_ack (struct mpr_softc*,int,int) ; 
 scalar_t__ mpr_wait_db_int (struct mpr_softc*) ; 

__attribute__((used)) static int
mpr_request_sync(struct mpr_softc *sc, void *req, MPI2_DEFAULT_REPLY *reply,
    int req_sz, int reply_sz, int timeout)
{
	uint32_t *data32;
	uint16_t *data16;
	int i, count, ioc_sz, residual;
	int sleep_flags = CAN_SLEEP;
	
#if __FreeBSD_version >= 1000029
	if (curthread->td_no_sleeping)
#else //__FreeBSD_version < 1000029
	if (curthread->td_pflags & TDP_NOSLEEPING)
#endif //__FreeBSD_version >= 1000029
		sleep_flags = NO_SLEEP;

	/* Step 1 */
	mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);

	/* Step 2 */
	if (mpr_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_USED)
		return (EBUSY);

	/* Step 3
	 * Announce that a message is coming through the doorbell.  Messages
	 * are pushed at 32bit words, so round up if needed.
	 */
	count = (req_sz + 3) / 4;
	mpr_regwrite(sc, MPI2_DOORBELL_OFFSET,
	    (MPI2_FUNCTION_HANDSHAKE << MPI2_DOORBELL_FUNCTION_SHIFT) |
	    (count << MPI2_DOORBELL_ADD_DWORDS_SHIFT));

	/* Step 4 */
	if (mpr_wait_db_int(sc) ||
	    (mpr_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_USED) == 0) {
		mpr_dprint(sc, MPR_FAULT, "Doorbell failed to activate\n");
		return (ENXIO);
	}
	mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	if (mpr_wait_db_ack(sc, 5, sleep_flags) != 0) {
		mpr_dprint(sc, MPR_FAULT, "Doorbell handshake failed\n");
		return (ENXIO);
	}

	/* Step 5 */
	/* Clock out the message data synchronously in 32-bit dwords*/
	data32 = (uint32_t *)req;
	for (i = 0; i < count; i++) {
		mpr_regwrite(sc, MPI2_DOORBELL_OFFSET, htole32(data32[i]));
		if (mpr_wait_db_ack(sc, 5, sleep_flags) != 0) {
			mpr_dprint(sc, MPR_FAULT,
			    "Timeout while writing doorbell\n");
			return (ENXIO);
		}
	}

	/* Step 6 */
	/* Clock in the reply in 16-bit words.  The total length of the
	 * message is always in the 4th byte, so clock out the first 2 words
	 * manually, then loop the rest.
	 */
	data16 = (uint16_t *)reply;
	if (mpr_wait_db_int(sc) != 0) {
		mpr_dprint(sc, MPR_FAULT, "Timeout reading doorbell 0\n");
		return (ENXIO);
	}
	data16[0] =
	    mpr_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_DATA_MASK;
	mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	if (mpr_wait_db_int(sc) != 0) {
		mpr_dprint(sc, MPR_FAULT, "Timeout reading doorbell 1\n");
		return (ENXIO);
	}
	data16[1] =
	    mpr_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_DATA_MASK;
	mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);

	/* Number of 32bit words in the message */
	ioc_sz = reply->MsgLength;

	/*
	 * Figure out how many 16bit words to clock in without overrunning.
	 * The precision loss with dividing reply_sz can safely be
	 * ignored because the messages can only be multiples of 32bits.
	 */
	residual = 0;
	count = MIN((reply_sz / 4), ioc_sz) * 2;
	if (count < ioc_sz * 2) {
		residual = ioc_sz * 2 - count;
		mpr_dprint(sc, MPR_ERROR, "Driver error, throwing away %d "
		    "residual message words\n", residual);
	}

	for (i = 2; i < count; i++) {
		if (mpr_wait_db_int(sc) != 0) {
			mpr_dprint(sc, MPR_FAULT,
			    "Timeout reading doorbell %d\n", i);
			return (ENXIO);
		}
		data16[i] = mpr_regread(sc, MPI2_DOORBELL_OFFSET) &
		    MPI2_DOORBELL_DATA_MASK;
		mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	}

	/*
	 * Pull out residual words that won't fit into the provided buffer.
	 * This keeps the chip from hanging due to a driver programming
	 * error.
	 */
	while (residual--) {
		if (mpr_wait_db_int(sc) != 0) {
			mpr_dprint(sc, MPR_FAULT, "Timeout reading doorbell\n");
			return (ENXIO);
		}
		(void)mpr_regread(sc, MPI2_DOORBELL_OFFSET);
		mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	}

	/* Step 7 */
	if (mpr_wait_db_int(sc) != 0) {
		mpr_dprint(sc, MPR_FAULT, "Timeout waiting to exit doorbell\n");
		return (ENXIO);
	}
	if (mpr_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_USED)
		mpr_dprint(sc, MPR_FAULT, "Warning, doorbell still active\n");
	mpr_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);

	return (0);
}