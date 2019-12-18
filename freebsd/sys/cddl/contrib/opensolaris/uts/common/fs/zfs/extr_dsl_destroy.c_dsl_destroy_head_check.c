#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  ddha_name; } ;
typedef  TYPE_1__ dsl_destroy_head_arg_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_destroy_head_check_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dsl_destroy_head_check(void *arg, dmu_tx_t *tx)
{
	dsl_destroy_head_arg_t *ddha = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	int error;

	error = dsl_dataset_hold(dp, ddha->ddha_name, FTAG, &ds);
	if (error != 0)
		return (error);

	error = dsl_destroy_head_check_impl(ds, 0);
	dsl_dataset_rele(ds, FTAG);
	return (error);
}