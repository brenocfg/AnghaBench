#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ pm_message_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  initcall_debug_report (struct device*,int /*<<< orphan*/ ,int (*) (struct device*,TYPE_1__),int) ; 
 int /*<<< orphan*/  initcall_debug_start (struct device*,int (*) (struct device*,TYPE_1__)) ; 
 int /*<<< orphan*/  suspend_report_result (int (*) (struct device*,TYPE_1__),int) ; 
 int /*<<< orphan*/  trace_device_pm_callback_end (struct device*,int) ; 
 int /*<<< orphan*/  trace_device_pm_callback_start (struct device*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int legacy_suspend(struct device *dev, pm_message_t state,
			  int (*cb)(struct device *dev, pm_message_t state),
			  const char *info)
{
	int error;
	ktime_t calltime;

	calltime = initcall_debug_start(dev, cb);

	trace_device_pm_callback_start(dev, info, state.event);
	error = cb(dev, state);
	trace_device_pm_callback_end(dev, error);
	suspend_report_result(cb, error);

	initcall_debug_report(dev, calltime, cb, error);

	return error;
}