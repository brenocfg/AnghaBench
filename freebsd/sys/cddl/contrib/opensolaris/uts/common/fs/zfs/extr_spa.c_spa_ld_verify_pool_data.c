#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_5__ {scalar_t__ spa_load_state; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_1__*,char*,int) ; 
 int spa_load_verify (TYPE_1__*) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
spa_ld_verify_pool_data(spa_t *spa)
{
	int error = 0;
	vdev_t *rvd = spa->spa_root_vdev;

	/*
	 * We've successfully opened the pool, verify that we're ready
	 * to start pushing transactions.
	 */
	if (spa->spa_load_state != SPA_LOAD_TRYIMPORT) {
		error = spa_load_verify(spa);
		if (error != 0) {
			spa_load_failed(spa, "spa_load_verify failed "
			    "[error=%d]", error);
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA,
			    error));
		}
	}

	return (0);
}