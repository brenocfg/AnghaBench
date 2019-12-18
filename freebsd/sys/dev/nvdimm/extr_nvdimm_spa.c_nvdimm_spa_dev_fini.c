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
struct nvdimm_spa_dev {int /*<<< orphan*/ * spa_kva; int /*<<< orphan*/  spa_len; int /*<<< orphan*/  spa_obj; int /*<<< orphan*/ * spa_dev; TYPE_1__* spa_g; } ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  nvdimm_spa_g_destroy_geom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_large_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

void
nvdimm_spa_dev_fini(struct nvdimm_spa_dev *dev)
{

	if (dev->spa_g != NULL) {
		g_topology_lock();
		nvdimm_spa_g_destroy_geom(NULL, dev->spa_g->class, dev->spa_g);
		g_topology_unlock();
	}
	if (dev->spa_dev != NULL) {
		destroy_dev(dev->spa_dev);
		dev->spa_dev = NULL;
	}
	vm_object_deallocate(dev->spa_obj);
	if (dev->spa_kva != NULL) {
		pmap_large_unmap(dev->spa_kva, dev->spa_len);
		dev->spa_kva = NULL;
	}
}