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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 int IR_FIRMODE ; 
 int IR_OFF ; 
 int IR_SIRMODE ; 
 int /*<<< orphan*/  pxa2xx_mfp_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_mfp_fir ; 
 int /*<<< orphan*/  pxa2xx_mfp_off ; 
 int /*<<< orphan*/  pxa2xx_mfp_sir ; 

void pxa2xx_transceiver_mode(struct device *dev, int mode)
{
	if (mode & IR_OFF) {
		pxa2xx_mfp_config(pxa2xx_mfp_off, ARRAY_SIZE(pxa2xx_mfp_off));
	} else if (mode & IR_SIRMODE) {
		pxa2xx_mfp_config(pxa2xx_mfp_sir, ARRAY_SIZE(pxa2xx_mfp_sir));
	} else if (mode & IR_FIRMODE) {
		pxa2xx_mfp_config(pxa2xx_mfp_fir, ARRAY_SIZE(pxa2xx_mfp_fir));
	} else
		BUG();
}