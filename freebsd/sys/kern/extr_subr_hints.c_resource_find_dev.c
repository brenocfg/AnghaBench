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
 int resource_find (int*,int*,char const*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
resource_find_dev(int *anchor, const char *name, int *unit,
    const char *resname, const char *value)
{
	int found_unit;
	int newln;
	int ret;

	newln = *anchor;
	ret = resource_find(anchor, &newln, name, NULL, resname, value,
	    NULL, NULL, &found_unit, NULL, NULL, NULL);
	if (ret == 0) {
		*unit = found_unit;
	}
	*anchor = newln;
	return ret;
}