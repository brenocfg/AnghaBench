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
typedef  int /*<<< orphan*/  zfs_refcount_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int spa_alloc_count; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  metaslab_ops_t ;
struct TYPE_6__ {int /*<<< orphan*/ * mc_alloc_slots; void* mc_alloc_max_slots; int /*<<< orphan*/  mc_lock; int /*<<< orphan*/ * mc_ops; int /*<<< orphan*/ * mc_rotor; TYPE_1__* mc_spa; } ;
typedef  TYPE_2__ metaslab_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_create_tracked (int /*<<< orphan*/ *) ; 

metaslab_class_t *
metaslab_class_create(spa_t *spa, metaslab_ops_t *ops)
{
	metaslab_class_t *mc;

	mc = kmem_zalloc(sizeof (metaslab_class_t), KM_SLEEP);

	mc->mc_spa = spa;
	mc->mc_rotor = NULL;
	mc->mc_ops = ops;
	mutex_init(&mc->mc_lock, NULL, MUTEX_DEFAULT, NULL);
	mc->mc_alloc_slots = kmem_zalloc(spa->spa_alloc_count *
	    sizeof (zfs_refcount_t), KM_SLEEP);
	mc->mc_alloc_max_slots = kmem_zalloc(spa->spa_alloc_count *
	    sizeof (uint64_t), KM_SLEEP);
	for (int i = 0; i < spa->spa_alloc_count; i++)
		zfs_refcount_create_tracked(&mc->mc_alloc_slots[i]);

	return (mc);
}