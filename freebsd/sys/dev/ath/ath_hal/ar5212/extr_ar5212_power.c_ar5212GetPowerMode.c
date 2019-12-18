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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_POWER_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SCR ; 
 int /*<<< orphan*/  AR_SCR_SLE ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_POWER_MODE
ar5212GetPowerMode(struct ath_hal *ah)
{
	/* Just so happens the h/w maps directly to the abstracted value */
	return MS(OS_REG_READ(ah, AR_SCR), AR_SCR_SLE);
}