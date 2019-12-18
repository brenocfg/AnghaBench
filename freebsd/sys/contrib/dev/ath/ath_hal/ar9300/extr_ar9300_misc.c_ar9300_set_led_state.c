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
typedef  int /*<<< orphan*/  const u_int32_t ;
struct ath_hal {int dummy; } ;
typedef  size_t HAL_LED_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CFG_LED ; 
#define  AR_CFG_LED_ASSOC_ACTIVE 130 
 int /*<<< orphan*/  AR_CFG_LED_ASSOC_CTL ; 
#define  AR_CFG_LED_ASSOC_NONE 129 
#define  AR_CFG_LED_ASSOC_PENDING 128 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

void
ar9300_set_led_state(struct ath_hal *ah, HAL_LED_STATE state)
{
    static const u_int32_t ledbits[8] = {
        AR_CFG_LED_ASSOC_NONE,     /* HAL_LED_RESET */
        AR_CFG_LED_ASSOC_PENDING,  /* HAL_LED_INIT  */
        AR_CFG_LED_ASSOC_PENDING,  /* HAL_LED_READY */
        AR_CFG_LED_ASSOC_PENDING,  /* HAL_LED_SCAN  */
        AR_CFG_LED_ASSOC_PENDING,  /* HAL_LED_AUTH  */
        AR_CFG_LED_ASSOC_ACTIVE,   /* HAL_LED_ASSOC */
        AR_CFG_LED_ASSOC_ACTIVE,   /* HAL_LED_RUN   */
        AR_CFG_LED_ASSOC_NONE,
    };

    OS_REG_RMW_FIELD(ah, AR_CFG_LED, AR_CFG_LED_ASSOC_CTL, ledbits[state]);
}