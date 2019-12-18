#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vib_object; int /*<<< orphan*/ * vib_entries; TYPE_1__* vib_phys; int /*<<< orphan*/ * vib_dbuf; int /*<<< orphan*/ * vib_objset; } ;
typedef  TYPE_2__ vdev_indirect_births_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ vib_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EQUIV (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
vdev_indirect_births_verify(vdev_indirect_births_t *vib)
{
	ASSERT(vib != NULL);

	ASSERT(vib->vib_object != 0);
	ASSERT(vib->vib_objset != NULL);
	ASSERT(vib->vib_phys != NULL);
	ASSERT(vib->vib_dbuf != NULL);

	EQUIV(vib->vib_phys->vib_count > 0, vib->vib_entries != NULL);

	return (B_TRUE);
}