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
struct of_device_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_register_data (int /*<<< orphan*/ *,char*,int,struct of_device_id const*,int) ; 
 struct of_device_id* ti_cpufreq_match_node () ; 

__attribute__((used)) static int ti_cpufreq_init(void)
{
	const struct of_device_id *match;

	/* Check to ensure we are on a compatible platform */
	match = ti_cpufreq_match_node();
	if (match)
		platform_device_register_data(NULL, "ti-cpufreq", -1, match,
					      sizeof(*match));

	return 0;
}