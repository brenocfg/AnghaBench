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
typedef  scalar_t__ uint64_t ;
struct sort_column {char* name; char* val; int /*<<< orphan*/  nvl; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  be_prop_list_free (int /*<<< orphan*/ *) ; 
 int fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
prop_list_sort(nvlist_t *props, char *property, bool reverse)
{
	nvpair_t *nvp;
	nvlist_t *nvl;
	int i, nvp_count;
	uint64_t lval, rval;
	struct sort_column sc_prev, sc_next;

	/* a temporary list to work with */
	nvlist_dup(props, &nvl, 0);

	nvp_count = fnvlist_num_pairs(nvl);
	for (i = 0; i < nvp_count; i++) {

		nvp = nvlist_next_nvpair(nvl, NULL);
		nvpair_value_nvlist(nvp, &sc_prev.nvl);
		nvlist_lookup_string(sc_prev.nvl, "name", &sc_prev.name);
		nvlist_lookup_string(sc_prev.nvl, property, &sc_prev.val);

		while ((nvp = nvlist_next_nvpair(nvl, nvp)) != NULL) {

			nvpair_value_nvlist(nvp, &sc_next.nvl);
			nvlist_lookup_string(sc_next.nvl, "name", &sc_next.name);
			nvlist_lookup_string(sc_next.nvl, property, &sc_next.val);

			/* properties that use numerical comparison */
			if (strcmp(property, "creation") == 0 ||
			    strcmp(property, "used") == 0 ||
			    strcmp(property, "usedds") == 0 ||
			    strcmp(property, "usedsnap") == 0 ||
			    strcmp(property, "usedrefreserv") == 0) {

				lval = strtoull(sc_prev.val, NULL, 10);
				rval = strtoull(sc_next.val, NULL, 10);

				if ((lval < rval && reverse) ||
				    (lval > rval && !reverse))
					sc_prev = sc_next;
			}

			/* properties that use string comparison */
			else if (strcmp(property, "name") == 0 ||
				 strcmp(property, "origin") == 0) {
				if ((strcmp(sc_prev.val, sc_next.val) < 0 && reverse) ||
				    (strcmp(sc_prev.val, sc_next.val) > 0 && !reverse))
					sc_prev = sc_next;
			}
		}

		/*
		 * The 'props' nvlist has been created to only have unique names.
		 * When a name is added, any existing nvlist's with the same name
		 * will be removed. Eventually, all existing nvlist's are replaced
		 * in sorted order.
		 */
		nvlist_add_nvlist(props, sc_prev.name, sc_prev.nvl);
		nvlist_remove_all(nvl, sc_prev.name);
	}

	be_prop_list_free(nvl);

	return 0;
}