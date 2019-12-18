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
struct wakeup_source {int /*<<< orphan*/ * wakeirq; } ;
struct TYPE_2__ {struct wakeup_source* wakeup; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */

void device_wakeup_detach_irq(struct device *dev)
{
	struct wakeup_source *ws;

	ws = dev->power.wakeup;
	if (ws)
		ws->wakeirq = NULL;
}