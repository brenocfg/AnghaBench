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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static const char *
get_origin_props(nvlist_t *dsprops, nvlist_t **originprops)
{
	char *propstr;

	if (nvlist_lookup_string(dsprops, "origin", &propstr) == 0) {
		if (be_prop_list_alloc(originprops) != 0) {
			fprintf(stderr,
			    "bectl list: failed to allocate origin prop nvlist\n");
			return (NULL);
		}
		if (be_get_dataset_props(be, propstr, *originprops) != 0) {
			/* XXX TODO: Real errors */
			fprintf(stderr,
			    "bectl list: failed to fetch origin properties\n");
			return (NULL);
		}

		return (propstr);
	}
	return (NULL);
}