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
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_FIND_SNAPSHOTS ; 
 int EEXIST ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  dmu_objset_find (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_prefetch ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dmu_snapshot_list_next (int /*<<< orphan*/ *,int,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int zvol_create_minor (char*) ; 

__attribute__((used)) static int
zvol_create_snapshots(objset_t *os, const char *name)
{
	uint64_t cookie, obj;
	char *sname;
	int error, len;

	cookie = obj = 0;
	sname = kmem_alloc(MAXPATHLEN, KM_SLEEP);

#if 0
	(void) dmu_objset_find(name, dmu_objset_prefetch, NULL,
	    DS_FIND_SNAPSHOTS);
#endif

	for (;;) {
		len = snprintf(sname, MAXPATHLEN, "%s@", name);
		if (len >= MAXPATHLEN) {
			dmu_objset_rele(os, FTAG);
			error = ENAMETOOLONG;
			break;
		}

		dsl_pool_config_enter(dmu_objset_pool(os), FTAG);
		error = dmu_snapshot_list_next(os, MAXPATHLEN - len,
		    sname + len, &obj, &cookie, NULL);
		dsl_pool_config_exit(dmu_objset_pool(os), FTAG);
		if (error != 0) {
			if (error == ENOENT)
				error = 0;
			break;
		}

		error = zvol_create_minor(sname);
		if (error != 0 && error != EEXIST) {
			printf("ZFS WARNING: Unable to create ZVOL %s (error=%d).\n",
			    sname, error);
			break;
		}
	}

	kmem_free(sname, MAXPATHLEN);
	return (error);
}