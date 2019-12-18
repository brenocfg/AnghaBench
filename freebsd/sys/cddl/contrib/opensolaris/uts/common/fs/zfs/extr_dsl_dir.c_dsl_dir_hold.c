#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_root_dir_obj; int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
typedef  int /*<<< orphan*/  ddobj ;
struct TYPE_7__ {int /*<<< orphan*/  dd_child_dir_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 int EXDEV ; 
 int SET_ERROR (int) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dprintf (char*,char const*,char const*,...) ; 
 int dsl_dir_hold_obj (TYPE_1__*,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ **) ; 
 TYPE_3__* dsl_dir_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,void*) ; 
 int dsl_pool_config_held (TYPE_1__*) ; 
 int getcomponent (char const*,char*,char const**) ; 
 char* spa_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *) ; 

int
dsl_dir_hold(dsl_pool_t *dp, const char *name, void *tag,
    dsl_dir_t **ddp, const char **tailp)
{
	char buf[ZFS_MAX_DATASET_NAME_LEN];
	const char *spaname, *next, *nextnext = NULL;
	int err;
	dsl_dir_t *dd;
	uint64_t ddobj;

	err = getcomponent(name, buf, &next);
	if (err != 0)
		return (err);

	/* Make sure the name is in the specified pool. */
	spaname = spa_name(dp->dp_spa);
	if (strcmp(buf, spaname) != 0)
		return (SET_ERROR(EXDEV));

	ASSERT(dsl_pool_config_held(dp));

	err = dsl_dir_hold_obj(dp, dp->dp_root_dir_obj, NULL, tag, &dd);
	if (err != 0) {
		return (err);
	}

	while (next != NULL) {
		dsl_dir_t *child_dd;
		err = getcomponent(next, buf, &nextnext);
		if (err != 0)
			break;
		ASSERT(next[0] != '\0');
		if (next[0] == '@')
			break;
		dprintf("looking up %s in obj%lld\n",
		    buf, dsl_dir_phys(dd)->dd_child_dir_zapobj);

		err = zap_lookup(dp->dp_meta_objset,
		    dsl_dir_phys(dd)->dd_child_dir_zapobj,
		    buf, sizeof (ddobj), 1, &ddobj);
		if (err != 0) {
			if (err == ENOENT)
				err = 0;
			break;
		}

		err = dsl_dir_hold_obj(dp, ddobj, buf, tag, &child_dd);
		if (err != 0)
			break;
		dsl_dir_rele(dd, tag);
		dd = child_dd;
		next = nextnext;
	}

	if (err != 0) {
		dsl_dir_rele(dd, tag);
		return (err);
	}

	/*
	 * It's an error if there's more than one component left, or
	 * tailp==NULL and there's any component left.
	 */
	if (next != NULL &&
	    (tailp == NULL || (nextnext && nextnext[0] != '\0'))) {
		/* bad path name */
		dsl_dir_rele(dd, tag);
		dprintf("next=%p (%s) tail=%p\n", next, next?next:"", tailp);
		err = SET_ERROR(ENOENT);
	}
	if (tailp != NULL)
		*tailp = next;
	*ddp = dd;
	return (err);
}