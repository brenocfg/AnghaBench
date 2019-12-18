#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  flow_ctrl_supported; } ;
struct al_eth_adapter {TYPE_1__ link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_FLOW_CTRL_RX_PAUSE ; 
 int /*<<< orphan*/  AL_ETH_FLOW_CTRL_TX_PAUSE ; 

__attribute__((used)) static inline void
al_eth_flow_ctrl_init(struct al_eth_adapter *adapter)
{
	uint8_t default_flow_ctrl;

	default_flow_ctrl = AL_ETH_FLOW_CTRL_TX_PAUSE;
	default_flow_ctrl |= AL_ETH_FLOW_CTRL_RX_PAUSE;

	adapter->link_config.flow_ctrl_supported = default_flow_ctrl;
}