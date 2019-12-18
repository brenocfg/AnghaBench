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
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_PROP_RECEIVE_RESUME_TOKEN ; 
 int /*<<< orphan*/  dsl_prop_nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* get_child_receive_stats (int /*<<< orphan*/ *) ; 
 char* get_receive_resume_stats_impl (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strfree (char*) ; 

__attribute__((used)) static void
get_receive_resume_stats(dsl_dataset_t *ds, nvlist_t *nv)
{
	char *propval = get_receive_resume_stats_impl(ds);
	if (strcmp(propval, "") != 0) {
		dsl_prop_nvlist_add_string(nv,
		    ZFS_PROP_RECEIVE_RESUME_TOKEN, propval);
	} else {
		char *childval = get_child_receive_stats(ds);
		if (strcmp(childval, "") != 0) {
			dsl_prop_nvlist_add_string(nv,
			    ZFS_PROP_RECEIVE_RESUME_TOKEN, childval);
		}
		strfree(childval);
	}
	strfree(propval);
}