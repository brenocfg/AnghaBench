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
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 int MPI_DOORBELL_FUNCTION_SHIFT ; 
 int MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET ; 
 scalar_t__ MPT_DB_IS_IN_USE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPT_DB_STATE_READY ; 
 scalar_t__ MPT_DB_STATE_RUNNING ; 
 int MPT_FAIL ; 
 int /*<<< orphan*/  MPT_OFFSET_DOORBELL ; 
 scalar_t__ MPT_OK ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 scalar_t__ MPT_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_rd_db (struct mpt_softc*) ; 
 scalar_t__ mpt_wait_db_ack (struct mpt_softc*) ; 
 scalar_t__ mpt_wait_state (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_write (struct mpt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_soft_reset(struct mpt_softc *mpt)
{

	mpt_lprt(mpt, MPT_PRT_DEBUG, "soft reset\n");

	/* Have to use hard reset if we are not in Running state */
	if (MPT_STATE(mpt_rd_db(mpt)) != MPT_DB_STATE_RUNNING) {
		mpt_prt(mpt, "soft reset failed: device not running\n");
		return (MPT_FAIL);
	}

	/* If door bell is in use we don't have a chance of getting
	 * a word in since the IOC probably crashed in message
	 * processing. So don't waste our time.
	 */
	if (MPT_DB_IS_IN_USE(mpt_rd_db(mpt))) {
		mpt_prt(mpt, "soft reset failed: doorbell wedged\n");
		return (MPT_FAIL);
	}

	/* Send the reset request to the IOC */
	mpt_write(mpt, MPT_OFFSET_DOORBELL,
	    MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET << MPI_DOORBELL_FUNCTION_SHIFT);
	if (mpt_wait_db_ack(mpt) != MPT_OK) {
		mpt_prt(mpt, "soft reset failed: ack timeout\n");
		return (MPT_FAIL);
	}

	/* Wait for the IOC to reload and come out of reset state */
	if (mpt_wait_state(mpt, MPT_DB_STATE_READY) != MPT_OK) {
		mpt_prt(mpt, "soft reset failed: device did not restart\n");
		return (MPT_FAIL);
	}

	return MPT_OK;
}