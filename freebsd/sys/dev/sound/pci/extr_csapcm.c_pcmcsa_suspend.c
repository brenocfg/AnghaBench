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
struct csa_info {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_AC97_POWERDOWN ; 
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA1_CIE ; 
 int /*<<< orphan*/  BA1_PFIE ; 
 int CLKCR1_SWCE ; 
 int /*<<< orphan*/  csa_ac97_suspend (struct csa_info*) ; 
 int /*<<< orphan*/  csa_active (struct csa_info*,int) ; 
 int csa_readmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_resetdsp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csa_stopcapturedma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_stopdsp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csa_stopplaydma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_writecodec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct csa_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcmcsa_suspend(device_t dev)
{
	struct csa_info *csa;
	csa_res *resp;

	csa = pcm_getdevinfo(dev);
	resp = &csa->res;

	csa_active(csa, 1);

	/* playback interrupt disable */
	csa_writemem(resp, BA1_PFIE,
	    (csa_readmem(resp, BA1_PFIE) & ~0x0000f03f) | 0x00000010);
	/* capture interrupt disable */
	csa_writemem(resp, BA1_CIE,
	    (csa_readmem(resp, BA1_CIE) & ~0x0000003f) | 0x00000011);
	csa_stopplaydma(csa);
	csa_stopcapturedma(csa);

	csa_ac97_suspend(csa);

	csa_resetdsp(resp);

	csa_stopdsp(resp);
	/*
	 *  Power down the DAC and ADC.  For now leave the other areas on.
	 */
	csa_writecodec(&csa->res, BA0_AC97_POWERDOWN, 0x300);
	/*
	 *  Power down the PLL.
	 */
	csa_writemem(resp, BA0_CLKCR1, 0);
	/*
	 * Turn off the Processor by turning off the software clock
	 * enable flag in the clock control register.
	 */
	csa_writemem(resp, BA0_CLKCR1,
	    csa_readmem(resp, BA0_CLKCR1) & ~CLKCR1_SWCE);

	csa_active(csa, -1);

	return 0;
}