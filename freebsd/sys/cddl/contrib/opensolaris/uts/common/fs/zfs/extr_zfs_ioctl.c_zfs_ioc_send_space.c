#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zbm_creation_txg; } ;
typedef  TYPE_1__ zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dmu_send_estimate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dmu_send_estimate_from_txg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_bookmark_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static int
zfs_ioc_send_space(const char *snapname, nvlist_t *innvl, nvlist_t *outnvl)
{
	dsl_pool_t *dp;
	dsl_dataset_t *tosnap;
	int error;
	char *fromname;
	boolean_t compressok;
	uint64_t space;

	error = dsl_pool_hold(snapname, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, snapname, FTAG, &tosnap);
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	compressok = nvlist_exists(innvl, "compressok");

	error = nvlist_lookup_string(innvl, "from", &fromname);
	if (error == 0) {
		if (strchr(fromname, '@') != NULL) {
			/*
			 * If from is a snapshot, hold it and use the more
			 * efficient dmu_send_estimate to estimate send space
			 * size using deadlists.
			 */
			dsl_dataset_t *fromsnap;
			error = dsl_dataset_hold(dp, fromname, FTAG, &fromsnap);
			if (error != 0)
				goto out;
			error = dmu_send_estimate(tosnap, fromsnap, compressok,
			    &space);
			dsl_dataset_rele(fromsnap, FTAG);
		} else if (strchr(fromname, '#') != NULL) {
			/*
			 * If from is a bookmark, fetch the creation TXG of the
			 * snapshot it was created from and use that to find
			 * blocks that were born after it.
			 */
			zfs_bookmark_phys_t frombm;

			error = dsl_bookmark_lookup(dp, fromname, tosnap,
			    &frombm);
			if (error != 0)
				goto out;
			error = dmu_send_estimate_from_txg(tosnap,
			    frombm.zbm_creation_txg, compressok, &space);
		} else {
			/*
			 * from is not properly formatted as a snapshot or
			 * bookmark
			 */
			error = SET_ERROR(EINVAL);
			goto out;
		}
	} else {
		/*
		 * If estimating the size of a full send, use dmu_send_estimate.
		 */
		error = dmu_send_estimate(tosnap, NULL, compressok, &space);
	}

	fnvlist_add_uint64(outnvl, "space", space);

out:
	dsl_dataset_rele(tosnap, FTAG);
	dsl_pool_rele(dp, FTAG);
	return (error);
}