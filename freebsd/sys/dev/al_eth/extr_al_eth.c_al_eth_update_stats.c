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
struct al_eth_mac_stats {int dummy; } ;
struct al_eth_adapter {scalar_t__ up; int /*<<< orphan*/  hal_adapter; struct al_eth_mac_stats mac_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_mac_stats_get (int /*<<< orphan*/ *,struct al_eth_mac_stats*) ; 

__attribute__((used)) static void*
al_eth_update_stats(struct al_eth_adapter *adapter)
{
	struct al_eth_mac_stats *mac_stats = &adapter->mac_stats;

	if (adapter->up == 0)
		return (NULL);

	al_eth_mac_stats_get(&adapter->hal_adapter, mac_stats);

	return (NULL);
}