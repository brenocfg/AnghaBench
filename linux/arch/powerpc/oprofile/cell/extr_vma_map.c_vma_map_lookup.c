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
typedef  unsigned int u32 ;
struct vma_to_fileoffset_map {unsigned int vma; unsigned int size; unsigned int guard_val; unsigned int offset; scalar_t__ guard_ptr; struct vma_to_fileoffset_map* next; } ;
struct spu {scalar_t__ local_store; } ;

/* Variables and functions */

unsigned int
vma_map_lookup(struct vma_to_fileoffset_map *map, unsigned int vma,
	       const struct spu *aSpu, int *grd_val)
{
	/*
	 * Default the offset to the physical address + a flag value.
	 * Addresses of dynamically generated code can't be found in the vma
	 * map.  For those addresses the flagged value will be sent on to
	 * the user space tools so they can be reported rather than just
	 * thrown away.
	 */
	u32 offset = 0x10000000 + vma;
	u32 ovly_grd;

	for (; map; map = map->next) {
		if (vma < map->vma || vma >= map->vma + map->size)
			continue;

		if (map->guard_ptr) {
			ovly_grd = *(u32 *)(aSpu->local_store + map->guard_ptr);
			if (ovly_grd != map->guard_val)
				continue;
			*grd_val = ovly_grd;
		}
		offset = vma - map->vma + map->offset;
		break;
	}

	return offset;
}