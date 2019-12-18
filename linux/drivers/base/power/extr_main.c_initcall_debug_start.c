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
struct device {scalar_t__ parent; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,void*,int /*<<< orphan*/ ,char*) ; 
 char* dev_name (scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  pm_print_times_enabled ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t initcall_debug_start(struct device *dev, void *cb)
{
	if (!pm_print_times_enabled)
		return 0;

	dev_info(dev, "calling %pS @ %i, parent: %s\n", cb,
		 task_pid_nr(current),
		 dev->parent ? dev_name(dev->parent) : "none");
	return ktime_get();
}