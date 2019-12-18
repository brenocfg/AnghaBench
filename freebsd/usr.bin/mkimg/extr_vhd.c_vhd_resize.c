#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct vhd_geom {int heads; int sectors; scalar_t__ cylinders; } ;
typedef  int int64_t ;

/* Variables and functions */
 int VHD_SECTOR_SIZE ; 
 int /*<<< orphan*/  vhd_geometry (int,struct vhd_geom*) ; 

__attribute__((used)) static uint64_t
vhd_resize(uint64_t origsz)
{
	struct vhd_geom geom;
	uint64_t newsz;

	/*
	 * Round the image size to the pre-determined geometry that
	 * matches the image size. This circular dependency implies
	 * that we need to loop to handle boundary conditions.
	 * The first time, newsz equals origsz and the geometry will
	 * typically yield a new size that's smaller. We keep adding
	 * cylinder's worth of sectors to the new size until its
	 * larger or equal or origsz. But during those iterations,
	 * the geometry can change, so we need to account for that.
	 */
	newsz = origsz;
	while (1) {
		vhd_geometry(newsz, &geom);
		newsz = (int64_t)geom.cylinders * geom.heads *
		    geom.sectors * VHD_SECTOR_SIZE;
		if (newsz >= origsz)
			break;
		newsz += geom.heads * geom.sectors * VHD_SECTOR_SIZE;
	}
	return (newsz);
}