#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_6__ {int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_7__ {scalar_t__ dp_tmp_userrefs_obj; int /*<<< orphan*/  dp_spa; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SPA_VERSION_USERREFS ; 
 int /*<<< orphan*/  dsl_dataset_user_release_tmp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
dsl_pool_clean_tmp_userrefs(dsl_pool_t *dp)
{
	zap_attribute_t za;
	zap_cursor_t zc;
	objset_t *mos = dp->dp_meta_objset;
	uint64_t zapobj = dp->dp_tmp_userrefs_obj;
	nvlist_t *holds;

	if (zapobj == 0)
		return;
	ASSERT(spa_version(dp->dp_spa) >= SPA_VERSION_USERREFS);

	holds = fnvlist_alloc();

	for (zap_cursor_init(&zc, mos, zapobj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		char *htag;
		nvlist_t *tags;

		htag = strchr(za.za_name, '-');
		*htag = '\0';
		++htag;
		if (nvlist_lookup_nvlist(holds, za.za_name, &tags) != 0) {
			tags = fnvlist_alloc();
			fnvlist_add_boolean(tags, htag);
			fnvlist_add_nvlist(holds, za.za_name, tags);
			fnvlist_free(tags);
		} else {
			fnvlist_add_boolean(tags, htag);
		}
	}
	dsl_dataset_user_release_tmp(dp, holds);
	fnvlist_free(holds);
	zap_cursor_fini(&zc);
}