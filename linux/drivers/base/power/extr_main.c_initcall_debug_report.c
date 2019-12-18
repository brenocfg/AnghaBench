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
struct device {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,void*,int,unsigned long long) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_print_times_enabled ; 

__attribute__((used)) static void initcall_debug_report(struct device *dev, ktime_t calltime,
				  void *cb, int error)
{
	ktime_t rettime;
	s64 nsecs;

	if (!pm_print_times_enabled)
		return;

	rettime = ktime_get();
	nsecs = (s64) ktime_to_ns(ktime_sub(rettime, calltime));

	dev_info(dev, "%pS returned %d after %Ld usecs\n", cb, error,
		 (unsigned long long)nsecs >> 10);
}