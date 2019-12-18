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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIODI ; 
 int AR_GPIOD_MASK ; 
 int AR_NUM_GPIO ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

uint32_t
ar5211GpioGet(struct ath_hal *ah, uint32_t gpio)
{
	if (gpio < AR_NUM_GPIO) {
		uint32_t val = OS_REG_READ(ah, AR_GPIODI);
		val = ((val & AR_GPIOD_MASK) >> gpio) & 0x1;
		return val;
	} else  {
		return 0xffffffff;
	}
}