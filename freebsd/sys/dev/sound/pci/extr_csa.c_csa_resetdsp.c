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
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_DREG ; 
 int /*<<< orphan*/  BA1_FRMT ; 
 int /*<<< orphan*/  BA1_SPCR ; 
 int /*<<< orphan*/  BA1_TWPR ; 
 int DREG_REGID_TRAP_SELECT ; 
 int SPCR_DRQEN ; 
 int SPCR_RSTSP ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
csa_resetdsp(csa_res *resp)
{
	int i;

	/*
	 * Write the reset bit of the SP control register.
	 */
	csa_writemem(resp, BA1_SPCR, SPCR_RSTSP);

	/*
	 * Write the control register.
	 */
	csa_writemem(resp, BA1_SPCR, SPCR_DRQEN);

	/*
	 * Clear the trap registers.
	 */
	for (i = 0 ; i < 8 ; i++) {
		csa_writemem(resp, BA1_DREG, DREG_REGID_TRAP_SELECT + i);
		csa_writemem(resp, BA1_TWPR, 0xffff);
	}
	csa_writemem(resp, BA1_DREG, 0);

	/*
	 * Set the frame timer to reflect the number of cycles per frame.
	 */
	csa_writemem(resp, BA1_FRMT, 0xadf);
}