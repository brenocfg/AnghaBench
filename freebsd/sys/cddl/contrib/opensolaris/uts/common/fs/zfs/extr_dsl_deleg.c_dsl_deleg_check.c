#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_dir_t ;
struct TYPE_4__ {int /*<<< orphan*/  dda_name; } ;
typedef  TYPE_1__ dsl_deleg_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_DELEGATED_PERMS ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dir_hold (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_deleg_check(void *arg, dmu_tx_t *tx)
{
	dsl_deleg_arg_t *dda = arg;
	dsl_dir_t *dd;
	int error;

	if (spa_version(dmu_tx_pool(tx)->dp_spa) <
	    SPA_VERSION_DELEGATED_PERMS) {
		return (SET_ERROR(ENOTSUP));
	}

	error = dsl_dir_hold(dmu_tx_pool(tx), dda->dda_name, FTAG, &dd, NULL);
	if (error == 0)
		dsl_dir_rele(dd, FTAG);
	return (error);
}