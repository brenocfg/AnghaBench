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
struct csa_info {int* ac97; int ac97_powerdown; int ac97_general_purpose; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 scalar_t__ BA0_AC97_GENERAL_PURPOSE ; 
 scalar_t__ BA0_AC97_HEADPHONE_VOLUME ; 
 scalar_t__ BA0_AC97_MASTER_VOLUME ; 
 scalar_t__ BA0_AC97_MASTER_VOLUME_MONO ; 
 scalar_t__ BA0_AC97_PCM_OUT_VOLUME ; 
 scalar_t__ BA0_AC97_POWERDOWN ; 
 scalar_t__ BA0_AC97_RESET ; 
 int CS461x_AC97_HIGHESTREGTORESTORE ; 
 int CS461x_AC97_NUMBER_RESTORE_REGS ; 
 int CS_AC97_POWER_CONTROL_ADC ; 
 int CS_AC97_POWER_CONTROL_DAC ; 
 int CS_AC97_POWER_CONTROL_MIXVON ; 
 int /*<<< orphan*/  csa_readcodec (int /*<<< orphan*/ *,scalar_t__,int*) ; 
 int /*<<< orphan*/  csa_writecodec (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
csa_ac97_suspend(struct csa_info *csa)
{
	int count, i;
	uint32_t tmp;

	for (count = 0x2, i=0;
	    (count <= CS461x_AC97_HIGHESTREGTORESTORE) &&
	    (i < CS461x_AC97_NUMBER_RESTORE_REGS);
	    count += 2, i++)
		csa_readcodec(&csa->res, BA0_AC97_RESET + count, &csa->ac97[i]);

	/* mute the outputs */
	csa_writecodec(&csa->res, BA0_AC97_MASTER_VOLUME, 0x8000);
	csa_writecodec(&csa->res, BA0_AC97_HEADPHONE_VOLUME, 0x8000);
	csa_writecodec(&csa->res, BA0_AC97_MASTER_VOLUME_MONO, 0x8000);
	csa_writecodec(&csa->res, BA0_AC97_PCM_OUT_VOLUME, 0x8000);
	/* save the registers that cause pops */
	csa_readcodec(&csa->res, BA0_AC97_POWERDOWN, &csa->ac97_powerdown);
	csa_readcodec(&csa->res, BA0_AC97_GENERAL_PURPOSE,
	    &csa->ac97_general_purpose);

	/*
	 * And power down everything on the AC97 codec. Well, for now,
	 * only power down the DAC/ADC and MIXER VREFON components.
	 * trouble with removing VREF.
	 */

	/* MIXVON */
	csa_readcodec(&csa->res, BA0_AC97_POWERDOWN, &tmp);
	csa_writecodec(&csa->res, BA0_AC97_POWERDOWN,
	    tmp | CS_AC97_POWER_CONTROL_MIXVON);
	/* ADC */
	csa_readcodec(&csa->res, BA0_AC97_POWERDOWN, &tmp);
	csa_writecodec(&csa->res, BA0_AC97_POWERDOWN,
	    tmp | CS_AC97_POWER_CONTROL_ADC);
	/* DAC */
	csa_readcodec(&csa->res, BA0_AC97_POWERDOWN, &tmp);
	csa_writecodec(&csa->res, BA0_AC97_POWERDOWN,
	    tmp | CS_AC97_POWER_CONTROL_DAC);
}