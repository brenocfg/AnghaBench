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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
#define  OMAP24XX_PWRDM_POWER_OFF 130 
#define  OMAP24XX_PWRDM_POWER_ON 129 
#define  OMAP24XX_PWRDM_POWER_RET 128 
 int PWRDM_POWER_OFF ; 
 int PWRDM_POWER_ON ; 
 int PWRDM_POWER_RET ; 

__attribute__((used)) static int omap2xxx_pwrst_to_common_pwrst(u8 omap2xxx_pwrst)
{
	u8 pwrst;

	switch (omap2xxx_pwrst) {
	case OMAP24XX_PWRDM_POWER_OFF:
		pwrst = PWRDM_POWER_OFF;
		break;
	case OMAP24XX_PWRDM_POWER_RET:
		pwrst = PWRDM_POWER_RET;
		break;
	case OMAP24XX_PWRDM_POWER_ON:
		pwrst = PWRDM_POWER_ON;
		break;
	default:
		return -EINVAL;
	}

	return pwrst;
}