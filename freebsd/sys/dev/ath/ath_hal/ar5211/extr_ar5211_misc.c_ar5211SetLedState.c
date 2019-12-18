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
 int const AR_PCICFG_LEDCTL ; 
#define  AR_PCICFG_LEDCTL_ASSOC 132 
#define  AR_PCICFG_LEDCTL_NONE 131 
#define  AR_PCICFG_LEDCTL_PEND 130 
 int const AR_PCICFG_LEDMODE ; 
#define  AR_PCICFG_LEDMODE_PROP 129 
#define  AR_PCICFG_LEDMODE_RAND 128 
 int const OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int const) ; 

void
ar5211SetLedState(struct ath_hal *ah, HAL_LED_STATE state)
{
	static const uint32_t ledbits[8] = {
		AR_PCICFG_LEDCTL_NONE|AR_PCICFG_LEDMODE_PROP, /* HAL_LED_INIT */
		AR_PCICFG_LEDCTL_PEND|AR_PCICFG_LEDMODE_PROP, /* HAL_LED_SCAN */
		AR_PCICFG_LEDCTL_PEND|AR_PCICFG_LEDMODE_PROP, /* HAL_LED_AUTH */
		AR_PCICFG_LEDCTL_ASSOC|AR_PCICFG_LEDMODE_PROP,/* HAL_LED_ASSOC*/
		AR_PCICFG_LEDCTL_ASSOC|AR_PCICFG_LEDMODE_PROP,/* HAL_LED_RUN */
		AR_PCICFG_LEDCTL_NONE|AR_PCICFG_LEDMODE_RAND,
		AR_PCICFG_LEDCTL_NONE|AR_PCICFG_LEDMODE_RAND,
		AR_PCICFG_LEDCTL_NONE|AR_PCICFG_LEDMODE_RAND,
	};
	OS_REG_WRITE(ah, AR_PCICFG,
		(OS_REG_READ(ah, AR_PCICFG) &~
			(AR_PCICFG_LEDCTL | AR_PCICFG_LEDMODE))
		| ledbits[state & 0x7]
	);
}