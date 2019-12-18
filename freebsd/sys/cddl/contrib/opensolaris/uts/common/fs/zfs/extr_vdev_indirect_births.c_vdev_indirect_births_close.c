#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* vib_phys; int /*<<< orphan*/ * vib_dbuf; scalar_t__ vib_object; int /*<<< orphan*/ * vib_objset; struct TYPE_9__* vib_entries; } ;
typedef  TYPE_2__ vdev_indirect_births_t ;
typedef  int uint64_t ;
struct TYPE_8__ {scalar_t__ vib_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int vdev_indirect_births_size_impl (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_indirect_births_verify (TYPE_2__*) ; 

void
vdev_indirect_births_close(vdev_indirect_births_t *vib)
{
	ASSERT(vdev_indirect_births_verify(vib));

	if (vib->vib_phys->vib_count > 0) {
		uint64_t births_size = vdev_indirect_births_size_impl(vib);

		kmem_free(vib->vib_entries, births_size);
		vib->vib_entries = NULL;
	}

	dmu_buf_rele(vib->vib_dbuf, vib);

	vib->vib_objset = NULL;
	vib->vib_object = 0;
	vib->vib_dbuf = NULL;
	vib->vib_phys = NULL;

	kmem_free(vib, sizeof (*vib));
}