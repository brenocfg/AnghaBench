#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* vib_phys; TYPE_3__* vib_entries; } ;
typedef  TYPE_2__ vdev_indirect_births_t ;
struct TYPE_8__ {int /*<<< orphan*/  vibe_phys_birth_txg; } ;
typedef  TYPE_3__ vdev_indirect_birth_entry_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int vib_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int vdev_indirect_births_verify (TYPE_2__*) ; 

uint64_t
vdev_indirect_births_last_entry_txg(vdev_indirect_births_t *vib)
{
	ASSERT(vdev_indirect_births_verify(vib));
	ASSERT(vib->vib_phys->vib_count > 0);

	vdev_indirect_birth_entry_phys_t *last =
	    &vib->vib_entries[vib->vib_phys->vib_count - 1];
	return (last->vibe_phys_birth_txg);
}