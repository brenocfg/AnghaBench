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
struct ftm_quaddec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_CNT ; 
 int /*<<< orphan*/  FTM_CNTIN ; 
 int /*<<< orphan*/  FTM_FLTCTRL ; 
 int /*<<< orphan*/  FTM_MOD ; 
 int /*<<< orphan*/  FTM_MODE ; 
 int FTM_MODE_FTMEN ; 
 int /*<<< orphan*/  FTM_POL ; 
 int /*<<< orphan*/  FTM_QDCTRL ; 
 int FTM_QDCTRL_QUADEN ; 
 int /*<<< orphan*/  FTM_SC ; 
 int FTM_SC_PS_1 ; 
 int /*<<< orphan*/  FTM_SYNC ; 
 int /*<<< orphan*/  FTM_SYNCONF ; 
 int /*<<< orphan*/  ftm_clear_write_protection (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_set_write_protection (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_write (struct ftm_quaddec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ftm_quaddec_init(struct ftm_quaddec *ftm)
{
	ftm_clear_write_protection(ftm);

	/*
	 * Do not write in the region from the CNTIN register through the
	 * PWMLOAD register when FTMEN = 0.
	 * Also reset other fields to zero
	 */
	ftm_write(ftm, FTM_MODE, FTM_MODE_FTMEN);
	ftm_write(ftm, FTM_CNTIN, 0x0000);
	ftm_write(ftm, FTM_MOD, 0xffff);
	ftm_write(ftm, FTM_CNT, 0x0);
	/* Set prescaler, reset other fields to zero */
	ftm_write(ftm, FTM_SC, FTM_SC_PS_1);

	/* Select quad mode, reset other fields to zero */
	ftm_write(ftm, FTM_QDCTRL, FTM_QDCTRL_QUADEN);

	/* Unused features and reset to default section */
	ftm_write(ftm, FTM_POL, 0x0);
	ftm_write(ftm, FTM_FLTCTRL, 0x0);
	ftm_write(ftm, FTM_SYNCONF, 0x0);
	ftm_write(ftm, FTM_SYNC, 0xffff);

	/* Lock the FTM */
	ftm_set_write_protection(ftm);
}