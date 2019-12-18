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
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_deleg_access_impl (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dsl_deleg_access(const char *dsname, const char *perm, cred_t *cr)
{
	dsl_pool_t *dp;
	dsl_dataset_t *ds;
	int error;

	error = dsl_pool_hold(dsname, FTAG, &dp);
	if (error != 0)
		return (error);
	error = dsl_dataset_hold(dp, dsname, FTAG, &ds);
	if (error == 0) {
		error = dsl_deleg_access_impl(ds, perm, cr);
		dsl_dataset_rele(ds, FTAG);
	}
	dsl_pool_rele(dp, FTAG);

	return (error);
}