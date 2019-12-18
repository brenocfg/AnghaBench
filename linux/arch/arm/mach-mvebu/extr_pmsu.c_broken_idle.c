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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int broken_idle(struct device_node *np)
{
	if (of_property_read_bool(np, "broken-idle")) {
		pr_warn("CPU idle is currently broken: disabling\n");
		return 1;
	}

	return 0;
}