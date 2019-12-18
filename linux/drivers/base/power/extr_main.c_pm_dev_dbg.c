#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_3__ {int event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 int PM_EVENT_SLEEP ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  pm_verb (int) ; 

__attribute__((used)) static void pm_dev_dbg(struct device *dev, pm_message_t state, const char *info)
{
	dev_dbg(dev, "%s%s%s\n", info, pm_verb(state.event),
		((state.event & PM_EVENT_SLEEP) && device_may_wakeup(dev)) ?
		", may wakeup" : "");
}