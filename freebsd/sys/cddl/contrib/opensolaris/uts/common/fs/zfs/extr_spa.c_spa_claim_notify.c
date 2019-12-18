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
struct TYPE_6__ {TYPE_1__* io_bp; scalar_t__ io_error; TYPE_3__* io_spa; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_7__ {scalar_t__ spa_claim_max_txg; int /*<<< orphan*/  spa_props_lock; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_5__ {scalar_t__ blk_birth; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
spa_claim_notify(zio_t *zio)
{
	spa_t *spa = zio->io_spa;

	if (zio->io_error)
		return;

	mutex_enter(&spa->spa_props_lock);	/* any mutex will do */
	if (spa->spa_claim_max_txg < zio->io_bp->blk_birth)
		spa->spa_claim_max_txg = zio->io_bp->blk_birth;
	mutex_exit(&spa->spa_props_lock);
}