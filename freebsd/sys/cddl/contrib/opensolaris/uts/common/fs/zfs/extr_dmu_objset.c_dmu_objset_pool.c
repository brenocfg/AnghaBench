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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  os_spa; TYPE_3__* os_dsl_dataset; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_7__ {TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/ * spa_get_dsl (int /*<<< orphan*/ ) ; 

dsl_pool_t *
dmu_objset_pool(objset_t *os)
{
	dsl_dataset_t *ds;

	if ((ds = os->os_dsl_dataset) != NULL && ds->ds_dir)
		return (ds->ds_dir->dd_pool);
	else
		return (spa_get_dsl(os->os_spa));
}