#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_13__ {int za_integer_length; int za_num_integers; scalar_t__ za_first_integer; char* za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_14__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_15__ {struct TYPE_15__* dd_parent; TYPE_2__* dd_pool; } ;
typedef  TYPE_3__ dsl_dir_t ;
struct TYPE_16__ {scalar_t__ dd_deleg_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_dir_hold (TYPE_2__*,char const*,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_name (TYPE_3__*,char*) ; 
 TYPE_8__* dsl_dir_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_pool_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ zap_count (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
dsl_deleg_get(const char *ddname, nvlist_t **nvp)
{
	dsl_dir_t *dd, *startdd;
	dsl_pool_t *dp;
	int error;
	objset_t *mos;

	error = dsl_pool_hold(ddname, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dir_hold(dp, ddname, FTAG, &startdd, NULL);
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	dp = startdd->dd_pool;
	mos = dp->dp_meta_objset;

	VERIFY(nvlist_alloc(nvp, NV_UNIQUE_NAME, KM_SLEEP) == 0);

	for (dd = startdd; dd != NULL; dd = dd->dd_parent) {
		zap_cursor_t basezc;
		zap_attribute_t baseza;
		nvlist_t *sp_nvp;
		uint64_t n;
		char source[ZFS_MAX_DATASET_NAME_LEN];

		if (dsl_dir_phys(dd)->dd_deleg_zapobj == 0 ||
		    zap_count(mos,
		    dsl_dir_phys(dd)->dd_deleg_zapobj, &n) != 0 || n == 0)
			continue;

		sp_nvp = fnvlist_alloc();
		for (zap_cursor_init(&basezc, mos,
		    dsl_dir_phys(dd)->dd_deleg_zapobj);
		    zap_cursor_retrieve(&basezc, &baseza) == 0;
		    zap_cursor_advance(&basezc)) {
			zap_cursor_t zc;
			zap_attribute_t za;
			nvlist_t *perms_nvp;

			ASSERT(baseza.za_integer_length == 8);
			ASSERT(baseza.za_num_integers == 1);

			perms_nvp = fnvlist_alloc();
			for (zap_cursor_init(&zc, mos, baseza.za_first_integer);
			    zap_cursor_retrieve(&zc, &za) == 0;
			    zap_cursor_advance(&zc)) {
				fnvlist_add_boolean(perms_nvp, za.za_name);
			}
			zap_cursor_fini(&zc);
			fnvlist_add_nvlist(sp_nvp, baseza.za_name, perms_nvp);
			fnvlist_free(perms_nvp);
		}

		zap_cursor_fini(&basezc);

		dsl_dir_name(dd, source);
		fnvlist_add_nvlist(*nvp, source, sp_nvp);
		nvlist_free(sp_nvp);
	}

	dsl_dir_rele(startdd, FTAG);
	dsl_pool_rele(dp, FTAG);
	return (0);
}