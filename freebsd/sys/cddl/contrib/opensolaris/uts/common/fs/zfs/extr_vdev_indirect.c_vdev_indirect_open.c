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
struct TYPE_3__ {scalar_t__ vdev_physical_ashift; scalar_t__ vdev_ashift; scalar_t__ vdev_asize; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ VDEV_LABEL_END_SIZE ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 

__attribute__((used)) static int
vdev_indirect_open(vdev_t *vd, uint64_t *psize, uint64_t *max_psize,
    uint64_t *logical_ashift, uint64_t *physical_ashift)
{
	*psize = *max_psize = vd->vdev_asize +
	    VDEV_LABEL_START_SIZE + VDEV_LABEL_END_SIZE;
	*logical_ashift = vd->vdev_ashift;
	*physical_ashift = vd->vdev_physical_ashift;
	return (0);
}