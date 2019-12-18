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
 int /*<<< orphan*/  bigsmp_dmi_table ; 
 scalar_t__ def_to_bigsmp ; 
 int dmi_bigsmp ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_bigsmp(void)
{
	if (def_to_bigsmp)
		dmi_bigsmp = 1;
	else
		dmi_check_system(bigsmp_dmi_table);

	return dmi_bigsmp;
}