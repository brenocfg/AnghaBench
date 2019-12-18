#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_refcount_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {scalar_t__ mc_alloc; scalar_t__ mc_deferred; scalar_t__ mc_space; scalar_t__ mc_dspace; int /*<<< orphan*/  mc_lock; TYPE_1__* mc_spa; struct TYPE_7__* mc_alloc_max_slots; struct TYPE_7__* mc_alloc_slots; int /*<<< orphan*/ * mc_rotor; } ;
typedef  TYPE_2__ metaslab_class_t ;
struct TYPE_6__ {int spa_alloc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (TYPE_2__*) ; 

void
metaslab_class_destroy(metaslab_class_t *mc)
{
	ASSERT(mc->mc_rotor == NULL);
	ASSERT(mc->mc_alloc == 0);
	ASSERT(mc->mc_deferred == 0);
	ASSERT(mc->mc_space == 0);
	ASSERT(mc->mc_dspace == 0);

	for (int i = 0; i < mc->mc_spa->spa_alloc_count; i++)
		zfs_refcount_destroy(&mc->mc_alloc_slots[i]);
	kmem_free(mc->mc_alloc_slots, mc->mc_spa->spa_alloc_count *
	    sizeof (zfs_refcount_t));
	kmem_free(mc->mc_alloc_max_slots, mc->mc_spa->spa_alloc_count *
	    sizeof (uint64_t));
	mutex_destroy(&mc->mc_lock);
	kmem_free(mc, sizeof (metaslab_class_t));
}