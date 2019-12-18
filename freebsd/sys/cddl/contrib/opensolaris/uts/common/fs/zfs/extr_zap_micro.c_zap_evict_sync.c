#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zap_num_entries_mtx; } ;
struct TYPE_6__ {TYPE_1__ zap_f; scalar_t__ zap_ismicro; int /*<<< orphan*/  zap_rwlock; } ;
typedef  TYPE_2__ zap_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mze_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 

void
zap_evict_sync(void *dbu)
{
	zap_t *zap = dbu;

	rw_destroy(&zap->zap_rwlock);

	if (zap->zap_ismicro)
		mze_destroy(zap);
	else
		mutex_destroy(&zap->zap_f.zap_num_entries_mtx);

	kmem_free(zap, sizeof (zap_t));
}