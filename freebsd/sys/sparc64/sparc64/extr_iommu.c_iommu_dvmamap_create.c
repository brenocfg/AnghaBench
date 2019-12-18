#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct iommu_state {int dummy; } ;
typedef  scalar_t__ bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_11__ {int dt_maxsize; int /*<<< orphan*/  dt_nsegments; struct iommu_state* dt_cookie; } ;
struct TYPE_10__ {int /*<<< orphan*/  dm_flags; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  DMF_COHERENT ; 
 scalar_t__ IOMMU_MAX_PRE ; 
 int /*<<< orphan*/  IOMMU_MAX_PRE_SEG ; 
 scalar_t__ IOMMU_SIZE_ROUNDUP (int) ; 
 int /*<<< orphan*/  IS_LOCK (struct iommu_state*) ; 
 int /*<<< orphan*/  IS_UNLOCK (struct iommu_state*) ; 
 int imin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iommu_dvma_valloc (TYPE_2__*,struct iommu_state*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  iommu_map_insq (struct iommu_state*,TYPE_1__*) ; 
 scalar_t__ round_io_page (scalar_t__) ; 
 int sparc64_dma_alloc_map (TYPE_2__*,TYPE_1__**) ; 
 scalar_t__ ulmin (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
iommu_dvmamap_create(bus_dma_tag_t dt, int flags, bus_dmamap_t *mapp)
{
	struct iommu_state *is = dt->dt_cookie;
	bus_size_t totsz, presz, currsz;
	int error, i, maxpre;

	if ((error = sparc64_dma_alloc_map(dt, mapp)) != 0)
		return (error);
	if ((flags & BUS_DMA_COHERENT) != 0)
		(*mapp)->dm_flags |= DMF_COHERENT;
	/*
	 * Preallocate DVMA space; if this fails now, it is retried at load
	 * time.  Through bus_dmamap_load_mbuf() and bus_dmamap_load_uio(),
	 * it is possible to have multiple discontiguous segments in a single
	 * map, which is handled by allocating additional resources, instead
	 * of increasing the size, to avoid fragmentation.
	 * Clamp preallocation to IOMMU_MAX_PRE.  In some situations we can
	 * handle more; that case is handled by reallocating at map load time.
	 */
	totsz = ulmin(IOMMU_SIZE_ROUNDUP(dt->dt_maxsize), IOMMU_MAX_PRE);
	error = iommu_dvma_valloc(dt, is, *mapp, totsz);
	if (error != 0)
		return (0);
	/*
	 * Try to be smart about preallocating some additional segments if
	 * needed.
	 */
	maxpre = imin(dt->dt_nsegments, IOMMU_MAX_PRE_SEG);
	presz = dt->dt_maxsize / maxpre;
	for (i = 1; i < maxpre && totsz < IOMMU_MAX_PRE; i++) {
		currsz = round_io_page(ulmin(presz, IOMMU_MAX_PRE - totsz));
		error = iommu_dvma_valloc(dt, is, *mapp, currsz);
		if (error != 0)
			break;
		totsz += currsz;
	}
	IS_LOCK(is);
	iommu_map_insq(is, *mapp);
	IS_UNLOCK(is);
	return (0);
}