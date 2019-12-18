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
 int am43xx_map_scu () ; 
 int amx3_common_init () ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int am43xx_suspend_init(void)
{
	int ret = 0;

	ret = am43xx_map_scu();
	if (ret) {
		pr_err("PM: Could not ioremap SCU\n");
		return ret;
	}

	ret = amx3_common_init();

	return ret;
}