#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 size_t MPI_DOORBELL_ADD_DWORDS_SHIFT ; 
 size_t MPI_DOORBELL_FUNCTION_SHIFT ; 
 size_t MPI_FUNCTION_HANDSHAKE ; 
 scalar_t__ MPT_DB_INTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MPT_DB_IS_IN_USE (size_t) ; 
 scalar_t__ MPT_DB_STATE_FAULT ; 
 scalar_t__ MPT_DB_STATE_READY ; 
 scalar_t__ MPT_DB_STATE_RUNNING ; 
 int /*<<< orphan*/  MPT_OFFSET_DOORBELL ; 
 int /*<<< orphan*/  MPT_OFFSET_INTR_STATUS ; 
 scalar_t__ MPT_OK ; 
 scalar_t__ MPT_STATE (size_t) ; 
 int /*<<< orphan*/  mpt_print_db (size_t) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 size_t mpt_rd_db (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_rd_intr (struct mpt_softc*) ; 
 scalar_t__ mpt_wait_db_ack (struct mpt_softc*) ; 
 scalar_t__ mpt_wait_db_int (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_write (struct mpt_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mpt_write_stream (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mpt_send_handshake_cmd(struct mpt_softc *mpt, size_t len, void *cmd)
{
	int i;
	uint32_t data, *data32;

	/* Check condition of the IOC */
	data = mpt_rd_db(mpt);
	if ((MPT_STATE(data) != MPT_DB_STATE_READY
	  && MPT_STATE(data) != MPT_DB_STATE_RUNNING
	  && MPT_STATE(data) != MPT_DB_STATE_FAULT)
	 || MPT_DB_IS_IN_USE(data)) {
		mpt_prt(mpt, "handshake aborted - invalid doorbell state\n");
		mpt_print_db(data);
		return (EBUSY);
	}

	/* We move things in 32 bit chunks */
	len = (len + 3) >> 2;
	data32 = cmd;

	/* Clear any left over pending doorbell interrupts */
	if (MPT_DB_INTR(mpt_rd_intr(mpt)))
		mpt_write(mpt, MPT_OFFSET_INTR_STATUS, 0);

	/*
	 * Tell the handshake reg. we are going to send a command
         * and how long it is going to be.
	 */
	data = (MPI_FUNCTION_HANDSHAKE << MPI_DOORBELL_FUNCTION_SHIFT) |
	    (len << MPI_DOORBELL_ADD_DWORDS_SHIFT);
	mpt_write(mpt, MPT_OFFSET_DOORBELL, data);

	/* Wait for the chip to notice */
	if (mpt_wait_db_int(mpt) != MPT_OK) {
		mpt_prt(mpt, "mpt_send_handshake_cmd: db ignored\n");
		return (ETIMEDOUT);
	}

	/* Clear the interrupt */
	mpt_write(mpt, MPT_OFFSET_INTR_STATUS, 0);

	if (mpt_wait_db_ack(mpt) != MPT_OK) {
		mpt_prt(mpt, "mpt_send_handshake_cmd: db ack timed out\n");
		return (ETIMEDOUT);
	}

	/* Send the command */
	for (i = 0; i < len; i++) {
		mpt_write_stream(mpt, MPT_OFFSET_DOORBELL, *data32++);
		if (mpt_wait_db_ack(mpt) != MPT_OK) {
			mpt_prt(mpt,
			    "mpt_send_handshake_cmd: timeout @ index %d\n", i);
			return (ETIMEDOUT);
		}
	}
	return MPT_OK;
}