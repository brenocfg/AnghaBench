#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_4__ {scalar_t__ dp_tmp_userrefs_obj; int /*<<< orphan*/  dp_spa; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_USERREFS ; 
 int dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_user_hold_create_obj (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* kmem_asprintf (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strfree (char*) ; 
 int zap_add (int /*<<< orphan*/ *,scalar_t__,char*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int zap_remove (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_pool_user_hold_rele_impl(dsl_pool_t *dp, uint64_t dsobj,
    const char *tag, uint64_t now, dmu_tx_t *tx, boolean_t holding)
{
	objset_t *mos = dp->dp_meta_objset;
	uint64_t zapobj = dp->dp_tmp_userrefs_obj;
	char *name;
	int error;

	ASSERT(spa_version(dp->dp_spa) >= SPA_VERSION_USERREFS);
	ASSERT(dmu_tx_is_syncing(tx));

	/*
	 * If the pool was created prior to SPA_VERSION_USERREFS, the
	 * zap object for temporary holds might not exist yet.
	 */
	if (zapobj == 0) {
		if (holding) {
			dsl_pool_user_hold_create_obj(dp, tx);
			zapobj = dp->dp_tmp_userrefs_obj;
		} else {
			return (SET_ERROR(ENOENT));
		}
	}

	name = kmem_asprintf("%llx-%s", (u_longlong_t)dsobj, tag);
	if (holding)
		error = zap_add(mos, zapobj, name, 8, 1, &now, tx);
	else
		error = zap_remove(mos, zapobj, name, tx);
	strfree(name);

	return (error);
}