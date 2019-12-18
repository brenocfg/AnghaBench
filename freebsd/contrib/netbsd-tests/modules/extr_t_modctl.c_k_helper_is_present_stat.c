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
 int get_modstat_info (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
k_helper_is_present_stat(void)
{

	return get_modstat_info("k_helper", NULL);
}