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
struct powernow_k8_data {int dummy; } ;

/* Variables and functions */
 struct powernow_k8_data* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernow_data ; 
 int query_current_values_with_pending_wait (struct powernow_k8_data*) ; 

__attribute__((used)) static void query_values_on_cpu(void *_err)
{
	int *err = _err;
	struct powernow_k8_data *data = __this_cpu_read(powernow_data);

	*err = query_current_values_with_pending_wait(data);
}