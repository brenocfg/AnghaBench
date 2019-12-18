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
struct al_eth_adapter {int /*<<< orphan*/  wd_callout; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
al_tick(void *arg)
{
	struct al_eth_adapter *adapter = arg;

	mii_tick(adapter->mii);

	/* Schedule another timeout one second from now */
	callout_schedule(&adapter->wd_callout, hz);
}