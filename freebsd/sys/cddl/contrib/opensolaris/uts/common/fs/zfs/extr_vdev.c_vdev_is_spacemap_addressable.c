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
struct TYPE_3__ {int vdev_ashift; unsigned long long vdev_asize; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_TRUE ; 
 int SM_OFFSET_BITS ; 
 int /*<<< orphan*/  SPA_FEATURE_SPACEMAP_V2 ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
vdev_is_spacemap_addressable(vdev_t *vd)
{
	if (spa_feature_is_active(vd->vdev_spa, SPA_FEATURE_SPACEMAP_V2))
		return (B_TRUE);

	/*
	 * If double-word space map entries are not enabled we assume
	 * 47 bits of the space map entry are dedicated to the entry's
	 * offset (see SM_OFFSET_BITS in space_map.h). We then use that
	 * to calculate the maximum address that can be described by a
	 * space map entry for the given device.
	 */
	uint64_t shift = vd->vdev_ashift + SM_OFFSET_BITS;

	if (shift >= 63) /* detect potential overflow */
		return (B_TRUE);

	return (vd->vdev_asize < (1ULL << shift));
}