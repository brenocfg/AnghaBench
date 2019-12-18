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

/* Variables and functions */
 int /*<<< orphan*/ * ac97_reset_config ; 
 int /*<<< orphan*/  pxa2xx_mfp_config (int /*<<< orphan*/ *,int) ; 

void pxa27x_configure_ac97reset(int reset_gpio, bool to_gpio)
{
	/*
	 * This helper function is used to work around a bug in the pxa27x's
	 * ac97 controller during a warm reset.  The configuration of the
	 * reset_gpio is changed as follows:
	 * to_gpio == true: configured to generic output gpio and driven high
	 * to_gpio == false: configured to ac97 controller alt fn AC97_nRESET
	 */

	if (reset_gpio == 113)
		pxa2xx_mfp_config(to_gpio ? &ac97_reset_config[0] :
				  &ac97_reset_config[1], 1);

	if (reset_gpio == 95)
		pxa2xx_mfp_config(to_gpio ? &ac97_reset_config[2] :
				  &ac97_reset_config[3], 1);
}