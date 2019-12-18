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
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_3__ {int /*<<< orphan*/  dp_meta_rootbp; int /*<<< orphan*/  dp_spa; int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_FLAG_MUSTSUCCEED ; 
 int /*<<< orphan*/  dmu_objset_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf_bp (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  spa_set_rootblkptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_pool_sync_mos(dsl_pool_t *dp, dmu_tx_t *tx)
{
	zio_t *zio = zio_root(dp->dp_spa, NULL, NULL, ZIO_FLAG_MUSTSUCCEED);
	dmu_objset_sync(dp->dp_meta_objset, zio, tx);
	VERIFY0(zio_wait(zio));
	dprintf_bp(&dp->dp_meta_rootbp, "meta objset rootbp is %s", "");
	spa_set_rootblkptr(dp->dp_spa, &dp->dp_meta_rootbp);
}