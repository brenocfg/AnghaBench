#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_6__ {TYPE_5__* spa_dsl_pool; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_first_txg; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 int dsl_pool_init (TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_1__*,char*,int) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_ld_open_rootbp(spa_t *spa)
{
	int error = 0;
	vdev_t *rvd = spa->spa_root_vdev;

	error = dsl_pool_init(spa, spa->spa_first_txg, &spa->spa_dsl_pool);
	if (error != 0) {
		spa_load_failed(spa, "unable to open rootbp in dsl_pool_init "
		    "[error=%d]", error);
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	}
	spa->spa_meta_objset = spa->spa_dsl_pool->dp_meta_objset;

	return (0);
}