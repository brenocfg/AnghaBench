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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* mac_regs_base; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  led_cfg; } ;
struct TYPE_4__ {TYPE_1__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_ACT_TIMER_MASK ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_ACT_TIMER_SHIFT ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_ACT_TIMER_VAL ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_BLINK_TIMER_MASK ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_BLINK_TIMER_SHIFT ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_BLINK_TIMER_VAL ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_SEL_DEFAULT_REG ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_SEL_LINK_ACTIVITY ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_SEL_MASK ; 
 int /*<<< orphan*/  ETH_MAC_GEN_LED_CFG_SEL_SHIFT ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_led_set(struct al_hal_eth_adapter *adapter, al_bool link_is_up)
{
	uint32_t reg = 0;
	uint32_t mode  = ETH_MAC_GEN_LED_CFG_SEL_DEFAULT_REG;

	if (link_is_up)
		mode = ETH_MAC_GEN_LED_CFG_SEL_LINK_ACTIVITY;

	AL_REG_FIELD_SET(reg,  ETH_MAC_GEN_LED_CFG_SEL_MASK,
			 ETH_MAC_GEN_LED_CFG_SEL_SHIFT, mode);

	AL_REG_FIELD_SET(reg, ETH_MAC_GEN_LED_CFG_BLINK_TIMER_MASK,
			 ETH_MAC_GEN_LED_CFG_BLINK_TIMER_SHIFT,
			 ETH_MAC_GEN_LED_CFG_BLINK_TIMER_VAL);

	AL_REG_FIELD_SET(reg, ETH_MAC_GEN_LED_CFG_ACT_TIMER_MASK,
			 ETH_MAC_GEN_LED_CFG_ACT_TIMER_SHIFT,
			 ETH_MAC_GEN_LED_CFG_ACT_TIMER_VAL);

	al_reg_write32(&adapter->mac_regs_base->gen.led_cfg, reg);

	return 0;
}