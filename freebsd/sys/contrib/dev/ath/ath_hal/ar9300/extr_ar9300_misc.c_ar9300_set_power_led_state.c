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
typedef  scalar_t__ u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CFG_LED ; 
 int /*<<< orphan*/  AR_CFG_LED_MODE_POWER_OFF ; 
 int /*<<< orphan*/  AR_CFG_LED_MODE_POWER_ON ; 
 int /*<<< orphan*/  AR_CFG_LED_POWER ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_set_power_led_state(struct ath_hal *ah, u_int8_t enabled)
{
    u_int32_t    val;

    val = enabled ? AR_CFG_LED_MODE_POWER_ON : AR_CFG_LED_MODE_POWER_OFF;
    OS_REG_RMW_FIELD(ah, AR_CFG_LED, AR_CFG_LED_POWER, val);
}