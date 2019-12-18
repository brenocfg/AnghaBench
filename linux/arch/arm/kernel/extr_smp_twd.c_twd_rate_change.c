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
struct notifier_block {int dummy; } ;
struct clk_notifier_data {int /*<<< orphan*/  new_rate; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 unsigned long POST_RATE_CHANGE ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  twd_update_frequency ; 

__attribute__((used)) static int twd_rate_change(struct notifier_block *nb,
	unsigned long flags, void *data)
{
	struct clk_notifier_data *cnd = data;

	/*
	 * The twd clock events must be reprogrammed to account for the new
	 * frequency.  The timer is local to a cpu, so cross-call to the
	 * changing cpu.
	 */
	if (flags == POST_RATE_CHANGE)
		on_each_cpu(twd_update_frequency,
				  (void *)&cnd->new_rate, 1);

	return NOTIFY_OK;
}