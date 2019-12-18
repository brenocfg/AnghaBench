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
 int dsl_dataset_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 char* kmem_asprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strfree (char*) ; 

int
dmu_objset_snapshot_one(const char *fsname, const char *snapname)
{
	int err;
	char *longsnap = kmem_asprintf("%s@%s", fsname, snapname);
	nvlist_t *snaps = fnvlist_alloc();

	fnvlist_add_boolean(snaps, longsnap);
	strfree(longsnap);
	err = dsl_dataset_snapshot(snaps, NULL, NULL);
	fnvlist_free(snaps);
	return (err);
}