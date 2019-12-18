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
typedef  int u_long ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_FRMT ; 
 int /*<<< orphan*/  BA1_SPCR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EAGAIN ; 
 int SPCR_DRQEN ; 
 int SPCR_RUN ; 
 int SPCR_RUNFR ; 
 int csa_readmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csa_startdsp(csa_res *resp)
{
	int i;
	u_long ul;

	/*
	 * Set the frame timer to reflect the number of cycles per frame.
	 */
	csa_writemem(resp, BA1_FRMT, 0xadf);

	/*
	 * Turn on the run, run at frame, and DMA enable bits in the local copy of
	 * the SP control register.
	 */
	csa_writemem(resp, BA1_SPCR, SPCR_RUN | SPCR_RUNFR | SPCR_DRQEN);

	/*
	 * Wait until the run at frame bit resets itself in the SP control
	 * register.
	 */
	ul = 0;
	for (i = 0 ; i < 25 ; i++) {
		/*
		 * Wait a little bit, so we don't issue PCI reads too frequently.
		 */
		DELAY(50);
		/*
		 * Fetch the current value of the SP status register.
		 */
		ul = csa_readmem(resp, BA1_SPCR);

		/*
		 * If the run at frame bit has reset, then stop waiting.
		 */
		if((ul & SPCR_RUNFR) == 0)
			break;
	}
	/*
	 * If the run at frame bit never reset, then return an error.
	 */
	if((ul & SPCR_RUNFR) != 0)
		return (EAGAIN);

	return (0);
}