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
 int resource_find (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const**,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* resource_string_copy (char const*,int) ; 

int
resource_find_match(int *anchor, const char **name, int *unit,
    const char *resname, const char *value)
{
	const char *found_name;
	int found_namelen;
	int found_unit;
	int ret;
	int newln;

	newln = *anchor;
	ret = resource_find(anchor, &newln, NULL, NULL, resname, value,
	    &found_name, &found_namelen, &found_unit, NULL, NULL, NULL);
	if (ret == 0) {
		*name = resource_string_copy(found_name, found_namelen);
		*unit = found_unit;
	}
	*anchor = newln;
	return ret;
}