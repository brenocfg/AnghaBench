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
struct TYPE_2__ {int (* prepare ) () ;} ;

/* Variables and functions */
 TYPE_1__* puv3_cpu_pm_fns ; 
 int stub1 () ; 

__attribute__((used)) static int puv3_pm_prepare(void)
{
	int ret = 0;

	if (puv3_cpu_pm_fns && puv3_cpu_pm_fns->prepare)
		ret = puv3_cpu_pm_fns->prepare();

	return ret;
}