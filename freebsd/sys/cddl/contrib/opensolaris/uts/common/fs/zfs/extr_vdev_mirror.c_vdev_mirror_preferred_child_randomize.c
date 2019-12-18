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
struct TYPE_5__ {int io_offset; TYPE_2__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {int mm_preferred_cnt; int* mm_preferred; scalar_t__ mm_root; } ;
typedef  TYPE_2__ mirror_map_t ;

/* Variables and functions */
 int spa_get_random (int) ; 
 int vdev_mirror_dva_select (TYPE_1__*,int) ; 
 int vdev_mirror_shift ; 

__attribute__((used)) static int
vdev_mirror_preferred_child_randomize(zio_t *zio)
{
	mirror_map_t *mm = zio->io_vsd;
	int p;

	if (mm->mm_root) {
		p = spa_get_random(mm->mm_preferred_cnt);
		return (vdev_mirror_dva_select(zio, p));
	}

	/*
	 * To ensure we don't always favour the first matching vdev,
	 * which could lead to wear leveling issues on SSD's, we
	 * use the I/O offset as a pseudo random seed into the vdevs
	 * which have the lowest load.
	 */
	p = (zio->io_offset >> vdev_mirror_shift) % mm->mm_preferred_cnt;
	return (mm->mm_preferred[p]);
}