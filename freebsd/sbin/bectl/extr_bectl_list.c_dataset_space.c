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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  be ; 
 scalar_t__ be_get_dataset_props (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ be_prop_list_alloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 unsigned long long strtoull (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long long
dataset_space(const char *oname)
{
	unsigned long long space;
	char *dsname, *propstr, *sep;
	nvlist_t *dsprops;

	space = 0;
	dsname = strdup(oname);
	if (dsname == NULL)
		return (0);

	/* Truncate snapshot to dataset name, as needed */
	if ((sep = strchr(dsname, '@')) != NULL)
		*sep = '\0';

	if (be_prop_list_alloc(&dsprops) != 0) {
		free(dsname);
		return (0);
	}

	if (be_get_dataset_props(be, dsname, dsprops) != 0) {
		nvlist_free(dsprops);
		free(dsname);
		return (0);
	}

	if (nvlist_lookup_string(dsprops, "used", &propstr) == 0)
		space = strtoull(propstr, NULL, 10);

	nvlist_free(dsprops);
	free(dsname);
	return (space);
}