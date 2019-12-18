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
struct mps_softc {int dummy; } ;
struct TYPE_5__ {scalar_t__ td_no_sleeping; } ;
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
 int /*<<< orphan*/  MPS_ERROR ; 
 int /*<<< orphan*/  MPS_FAULT ; 
 int NO_SLEEP ; 
 TYPE_3__* curthread ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int mps_regread (struct mps_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_regwrite (struct mps_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mps_wait_db_ack (struct mps_softc*,int,int) ; 
 scalar_t__ mps_wait_db_int (struct mps_softc*) ; 

__attribute__((used)) static int
mps_request_sync(struct mps_softc *sc, void *req, MPI2_DEFAULT_REPLY *reply,
    int req_sz, int reply_sz, int timeout)
{
	uint32_t *data32;
	uint16_t *data16;
	int i, count, ioc_sz, residual;
	int sleep_flags = CAN_SLEEP;

	if (curthread->td_no_sleeping != 0)
		sleep_flags = NO_SLEEP;

	/* Step 1 */
	mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);

	/* Step 2 */
	if (mps_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_USED)
		return (EBUSY);

	/* Step 3
	 * Announce that a message is coming through the doorbell.  Messages
	 * are pushed at 32bit words, so round up if needed.
	 */
	count = (req_sz + 3) / 4;
	mps_regwrite(sc, MPI2_DOORBELL_OFFSET,
	    (MPI2_FUNCTION_HANDSHAKE << MPI2_DOORBELL_FUNCTION_SHIFT) |
	    (count << MPI2_DOORBELL_ADD_DWORDS_SHIFT));

	/* Step 4 */
	if (mps_wait_db_int(sc) ||
	    (mps_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_USED) == 0) {
		mps_dprint(sc, MPS_FAULT, "Doorbell failed to activate\n");
		return (ENXIO);
	}
	mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	if (mps_wait_db_ack(sc, 5, sleep_flags) != 0) {
		mps_dprint(sc, MPS_FAULT, "Doorbell handshake failed\n");
		return (ENXIO);
	}

	/* Step 5 */
	/* Clock out the message data synchronously in 32-bit dwords*/
	data32 = (uint32_t *)req;
	for (i = 0; i < count; i++) {
		mps_regwrite(sc, MPI2_DOORBELL_OFFSET, htole32(data32[i]));
		if (mps_wait_db_ack(sc, 5, sleep_flags) != 0) {
			mps_dprint(sc, MPS_FAULT,
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
	if (mps_wait_db_int(sc) != 0) {
		mps_dprint(sc, MPS_FAULT, "Timeout reading doorbell 0\n");
		return (ENXIO);
	}
	data16[0] =
	    mps_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_DATA_MASK;
	mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	if (mps_wait_db_int(sc) != 0) {
		mps_dprint(sc, MPS_FAULT, "Timeout reading doorbell 1\n");
		return (ENXIO);
	}
	data16[1] =
	    mps_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_DATA_MASK;
	mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);

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
		mps_dprint(sc, MPS_ERROR, "Driver error, throwing away %d "
		    "residual message words\n", residual);
	}

	for (i = 2; i < count; i++) {
		if (mps_wait_db_int(sc) != 0) {
			mps_dprint(sc, MPS_FAULT,
			    "Timeout reading doorbell %d\n", i);
			return (ENXIO);
		}
		data16[i] = mps_regread(sc, MPI2_DOORBELL_OFFSET) &
		    MPI2_DOORBELL_DATA_MASK;
		mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	}

	/*
	 * Pull out residual words that won't fit into the provided buffer.
	 * This keeps the chip from hanging due to a driver programming
	 * error.
	 */
	while (residual--) {
		if (mps_wait_db_int(sc) != 0) {
			mps_dprint(sc, MPS_FAULT,
			    "Timeout reading doorbell\n");
			return (ENXIO);
		}
		(void)mps_regread(sc, MPI2_DOORBELL_OFFSET);
		mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);
	}

	/* Step 7 */
	if (mps_wait_db_int(sc) != 0) {
		mps_dprint(sc, MPS_FAULT, "Timeout waiting to exit doorbell\n");
		return (ENXIO);
	}
	if (mps_regread(sc, MPI2_DOORBELL_OFFSET) & MPI2_DOORBELL_USED)
		mps_dprint(sc, MPS_FAULT, "Warning, doorbell still active\n");
	mps_regwrite(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET, 0x0);

	return (0);
}