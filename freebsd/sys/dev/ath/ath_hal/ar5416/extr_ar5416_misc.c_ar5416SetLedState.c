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
typedef  int /*<<< orphan*/  const uint32_t ;
struct ath_hal {int dummy; } ;
typedef  int HAL_LED_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MAC_LED ; 
 int /*<<< orphan*/  AR_MAC_LED_ASSOC ; 
#define  AR_MAC_LED_ASSOC_ACTIVE 130 
#define  AR_MAC_LED_ASSOC_NONE 129 
#define  AR_MAC_LED_ASSOC_PEND 128 
 int /*<<< orphan*/  AR_MAC_LED_MODE ; 
 int /*<<< orphan*/  const AR_MAC_LED_MODE_PROP ; 
 scalar_t__ AR_SREV_HOWL (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

void
ar5416SetLedState(struct ath_hal *ah, HAL_LED_STATE state)
{
	static const uint32_t ledbits[8] = {
		AR_MAC_LED_ASSOC_NONE,		/* HAL_LED_INIT */
		AR_MAC_LED_ASSOC_PEND,		/* HAL_LED_SCAN */
		AR_MAC_LED_ASSOC_PEND,		/* HAL_LED_AUTH */
		AR_MAC_LED_ASSOC_ACTIVE,	/* HAL_LED_ASSOC*/
		AR_MAC_LED_ASSOC_ACTIVE,	/* HAL_LED_RUN */
		AR_MAC_LED_ASSOC_NONE,
		AR_MAC_LED_ASSOC_NONE,
		AR_MAC_LED_ASSOC_NONE,
	};

	if (AR_SREV_HOWL(ah))
		return;

	/*
	 * Set the blink operating mode.
	 */
	OS_REG_RMW_FIELD(ah, AR_MAC_LED,
	    AR_MAC_LED_ASSOC, ledbits[state & 0x7]);

	/* XXX Blink slow mode? */
	/* XXX Blink threshold? */
	/* XXX Blink sleep hystersis? */

	/*
	 * Set the LED blink configuration to be proportional
	 * to the current TX and RX filter bytes.  (Ie, RX'ed
	 * frames that don't match the filter are ignored.)
	 * This means that higher TX/RX throughput will result
	 * in the blink rate increasing.
	 */
	OS_REG_RMW_FIELD(ah, AR_MAC_LED, AR_MAC_LED_MODE,
	    AR_MAC_LED_MODE_PROP);
}