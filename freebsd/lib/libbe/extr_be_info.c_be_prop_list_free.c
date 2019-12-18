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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

void
be_prop_list_free(nvlist_t *be_list)
{
	nvlist_t *prop_list;
	nvpair_t *be_pair;

	be_pair = nvlist_next_nvpair(be_list, NULL);
	if (nvpair_value_nvlist(be_pair, &prop_list) == 0)
		nvlist_free(prop_list);

	while ((be_pair = nvlist_next_nvpair(be_list, be_pair)) != NULL) {
		if (nvpair_value_nvlist(be_pair, &prop_list) == 0)
			nvlist_free(prop_list);
	}
}