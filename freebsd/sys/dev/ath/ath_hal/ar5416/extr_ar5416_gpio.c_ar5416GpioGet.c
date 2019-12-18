#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ halNumGpioPins; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR9285_GPIO_IN_VAL ; 
 int /*<<< orphan*/  AR9287_GPIO_IN_VAL ; 
 int /*<<< orphan*/  AR928X_GPIO_IN_VAL ; 
 scalar_t__ AR_GPIO_BIT (scalar_t__) ; 
 int /*<<< orphan*/  AR_GPIO_IN_OUT ; 
 int /*<<< orphan*/  AR_GPIO_IN_VAL ; 
 scalar_t__ AR_SREV_KITE_10_OR_LATER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_KIWI_10_OR_LATER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_MERLIN_10_OR_LATER (struct ath_hal*) ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

uint32_t
ar5416GpioGet(struct ath_hal *ah, uint32_t gpio)
{
	uint32_t bits;

	if (gpio >= AH_PRIVATE(ah)->ah_caps.halNumGpioPins)
		return 0xffffffff;
	/*
	 * Read output value for all gpio's, shift it,
	 * and verify whether the specific bit is set.
	 */
	if (AR_SREV_KIWI_10_OR_LATER(ah))
		bits = MS(OS_REG_READ(ah, AR_GPIO_IN_OUT), AR9287_GPIO_IN_VAL);
	if (AR_SREV_KITE_10_OR_LATER(ah))
		bits = MS(OS_REG_READ(ah, AR_GPIO_IN_OUT), AR9285_GPIO_IN_VAL);
	else if (AR_SREV_MERLIN_10_OR_LATER(ah))
		bits = MS(OS_REG_READ(ah, AR_GPIO_IN_OUT), AR928X_GPIO_IN_VAL);
	else
		bits = MS(OS_REG_READ(ah, AR_GPIO_IN_OUT), AR_GPIO_IN_VAL);
	return ((bits & AR_GPIO_BIT(gpio)) != 0);
}