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
typedef  int uint32_t ;
struct mpt_softc {int /*<<< orphan*/ * fw_image; scalar_t__ is_1078; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int MPI_DIAG_DISABLE_ARM ; 
 int MPI_DIAG_RESET_ADAPTER ; 
 int /*<<< orphan*/  MPT_OFFSET_DIAGNOSTIC ; 
 int /*<<< orphan*/  MPT_OFFSET_RESET_1078 ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  mpt_disable_diag_mode (struct mpt_softc*) ; 
 int mpt_download_fw (struct mpt_softc*) ; 
 int mpt_enable_diag_mode (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int mpt_read (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_write (struct mpt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_hard_reset(struct mpt_softc *mpt)
{
	int error;
	int wait;
	uint32_t diagreg;

	mpt_lprt(mpt, MPT_PRT_DEBUG, "hard reset\n");

	if (mpt->is_1078) {
		mpt_write(mpt, MPT_OFFSET_RESET_1078, 0x07);
		DELAY(1000);
		return;
	}

	error = mpt_enable_diag_mode(mpt);
	if (error) {
		mpt_prt(mpt, "WARNING - Could not enter diagnostic mode !\n");
		mpt_prt(mpt, "Trying to reset anyway.\n");
	}

	diagreg = mpt_read(mpt, MPT_OFFSET_DIAGNOSTIC);

	/*
	 * This appears to be a workaround required for some
	 * firmware or hardware revs.
	 */
	mpt_write(mpt, MPT_OFFSET_DIAGNOSTIC, diagreg | MPI_DIAG_DISABLE_ARM);
	DELAY(1000);

	/* Diag. port is now active so we can now hit the reset bit */
	mpt_write(mpt, MPT_OFFSET_DIAGNOSTIC, diagreg | MPI_DIAG_RESET_ADAPTER);

        /*
         * Ensure that the reset has finished.  We delay 1ms
         * prior to reading the register to make sure the chip
         * has sufficiently completed its reset to handle register
         * accesses.
         */
	wait = 5000;
	do {
		DELAY(1000);
		diagreg = mpt_read(mpt, MPT_OFFSET_DIAGNOSTIC);
	} while (--wait && (diagreg & MPI_DIAG_RESET_ADAPTER) == 0);

	if (wait == 0) {
		mpt_prt(mpt, "WARNING - Failed hard reset! "
			"Trying to initialize anyway.\n");
	}

	/*
	 * If we have firmware to download, it must be loaded before
	 * the controller will become operational.  Do so now.
	 */
	if (mpt->fw_image != NULL) {

		error = mpt_download_fw(mpt);

		if (error) {
			mpt_prt(mpt, "WARNING - Firmware Download Failed!\n");
			mpt_prt(mpt, "Trying to initialize anyway.\n");
		}
	}

	/*
	 * Reseting the controller should have disabled write
	 * access to the diagnostic registers, but disable
	 * manually to be sure.
	 */
	mpt_disable_diag_mode(mpt);
}