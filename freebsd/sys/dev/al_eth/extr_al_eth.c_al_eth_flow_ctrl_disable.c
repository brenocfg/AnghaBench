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
struct TYPE_2__ {scalar_t__ flow_ctrl_active; } ;
struct al_eth_adapter {TYPE_1__ link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_flow_ctrl_config (struct al_eth_adapter*) ; 

__attribute__((used)) static void
al_eth_flow_ctrl_disable(struct al_eth_adapter *adapter)
{

	adapter->link_config.flow_ctrl_active = 0;
	al_eth_flow_ctrl_config(adapter);
}