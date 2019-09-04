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
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 

int lookup_config(const char **mapping, int nr_mapping, const char *var)
{
	int i;

	for (i = 0; i < nr_mapping; i++) {
		const char *name = mapping[i];

		if (name && !strcasecmp(var, name))
			return i;
	}
	return -1;
}