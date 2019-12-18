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
 int /*<<< orphan*/  ipmi_platform_driver ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int platform_registered ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

void ipmi_si_platform_init(void)
{
	int rv = platform_driver_register(&ipmi_platform_driver);
	if (rv)
		pr_err("Unable to register driver: %d\n", rv);
	else
		platform_registered = true;
}