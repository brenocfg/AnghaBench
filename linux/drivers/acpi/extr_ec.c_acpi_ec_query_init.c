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

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_max_queries ; 
 scalar_t__ ec_query_wq ; 

__attribute__((used)) static inline int acpi_ec_query_init(void)
{
	if (!ec_query_wq) {
		ec_query_wq = alloc_workqueue("kec_query", 0,
					      ec_max_queries);
		if (!ec_query_wq)
			return -ENODEV;
	}
	return 0;
}