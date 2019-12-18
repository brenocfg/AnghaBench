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
struct csa_info {int /*<<< orphan*/  rch; int /*<<< orphan*/  pch; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA0_HISR ; 
 int /*<<< orphan*/  BA1_CIE ; 
 int /*<<< orphan*/  BA1_PFIE ; 
 int ENXIO ; 
 int HICR_CHGM ; 
 int HICR_IEV ; 
 int HISR_INTENA ; 
 int /*<<< orphan*/  csa_ac97_resume (struct csa_info*) ; 
 int /*<<< orphan*/  csa_active (struct csa_info*,int) ; 
 int csa_readio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int csa_readmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_setupchan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csa_startcapturedma (struct csa_info*) ; 
 scalar_t__ csa_startdsp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csa_startplaydma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_stopcapturedma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_stopplaydma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_writeio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct csa_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcmcsa_resume(device_t dev)
{
	struct csa_info *csa;
	csa_res *resp;

	csa = pcm_getdevinfo(dev);
	resp = &csa->res;

	csa_active(csa, 1);

	/* cs_hardware_init */
	csa_stopplaydma(csa);
	csa_stopcapturedma(csa);
	csa_ac97_resume(csa);
	if (csa_startdsp(resp))
		return (ENXIO);
	/* Enable interrupts on the part. */
	if ((csa_readio(resp, BA0_HISR) & HISR_INTENA) == 0)
		csa_writeio(resp, BA0_HICR, HICR_IEV | HICR_CHGM);
	/* playback interrupt enable */
	csa_writemem(resp, BA1_PFIE, csa_readmem(resp, BA1_PFIE) & ~0x0000f03f);
	/* capture interrupt enable */
	csa_writemem(resp, BA1_CIE,
	    (csa_readmem(resp, BA1_CIE) & ~0x0000003f) | 0x00000001);
	/* cs_restart_part */
	csa_setupchan(&csa->pch);
	csa_startplaydma(csa);
	csa_setupchan(&csa->rch);
	csa_startcapturedma(csa);

	csa_active(csa, -1);

	return 0;
}