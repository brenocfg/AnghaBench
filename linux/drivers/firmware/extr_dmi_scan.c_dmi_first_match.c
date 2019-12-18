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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmi_is_end_of_table (struct dmi_system_id const*) ; 
 scalar_t__ dmi_matches (struct dmi_system_id const*) ; 

const struct dmi_system_id *dmi_first_match(const struct dmi_system_id *list)
{
	const struct dmi_system_id *d;

	for (d = list; !dmi_is_end_of_table(d); d++)
		if (dmi_matches(d))
			return d;

	return NULL;
}