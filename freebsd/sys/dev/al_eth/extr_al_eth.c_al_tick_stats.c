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
struct al_eth_adapter {int /*<<< orphan*/  stats_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_update_stats (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
al_tick_stats(void *arg)
{
	struct al_eth_adapter *adapter = arg;

	al_eth_update_stats(adapter);

	callout_schedule(&adapter->stats_callout, hz);
}