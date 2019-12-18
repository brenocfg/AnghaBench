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
typedef  int HAL_LED_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PCICFG ; 
 int AR_PCICFG_LED_ACT ; 
 int AR_PCICFG_LED_PEND ; 
#define  HAL_LED_INIT 129 
#define  HAL_LED_RUN 128 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5210SetLedState(struct ath_hal *ah, HAL_LED_STATE state)
{
	uint32_t val;

	val = OS_REG_READ(ah, AR_PCICFG);
	switch (state) {
	case HAL_LED_INIT:
		val &= ~(AR_PCICFG_LED_PEND | AR_PCICFG_LED_ACT);
		break;
	case HAL_LED_RUN:
		/* normal blink when connected */
		val &= ~AR_PCICFG_LED_PEND;
		val |= AR_PCICFG_LED_ACT;
		break;
	default:
		val |= AR_PCICFG_LED_PEND;
		val &= ~AR_PCICFG_LED_ACT;
		break;
	}
	OS_REG_WRITE(ah, AR_PCICFG, val);
}