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

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 unsigned long POST_RATE_CHANGE ; 
 unsigned long PRE_RATE_CHANGE ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int g12a_cpu_clk_mux_notifier_cb(struct notifier_block *nb,
					unsigned long event, void *data)
{
	if (event == POST_RATE_CHANGE || event == PRE_RATE_CHANGE) {
		/* Wait for clock propagation before/after changing the mux */
		udelay(100);
		return NOTIFY_OK;
	}

	return NOTIFY_DONE;
}