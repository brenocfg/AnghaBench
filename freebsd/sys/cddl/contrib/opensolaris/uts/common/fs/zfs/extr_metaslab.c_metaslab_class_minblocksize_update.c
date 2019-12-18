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
struct TYPE_5__ {unsigned long long vdev_ashift; } ;
typedef  TYPE_1__ vdev_t ;
typedef  unsigned long long uint64_t ;
struct TYPE_6__ {TYPE_1__* mg_vd; struct TYPE_6__* mg_next; } ;
typedef  TYPE_2__ metaslab_group_t ;
struct TYPE_7__ {unsigned long long mc_minblocksize; TYPE_2__* mc_rotor; } ;
typedef  TYPE_3__ metaslab_class_t ;

/* Variables and functions */
 unsigned long long SPA_MINBLOCKSIZE ; 
 unsigned long long UINT64_MAX ; 

void
metaslab_class_minblocksize_update(metaslab_class_t *mc)
{
	metaslab_group_t *mg;
	vdev_t *vd;
	uint64_t minashift = UINT64_MAX;

	if ((mg = mc->mc_rotor) == NULL) {
		mc->mc_minblocksize = SPA_MINBLOCKSIZE;
		return;
	}

	do {
		vd = mg->mg_vd;
		if (vd->vdev_ashift < minashift)
			minashift = vd->vdev_ashift;
	} while ((mg = mg->mg_next) != mc->mc_rotor);

	mc->mc_minblocksize = 1ULL << minashift;
}