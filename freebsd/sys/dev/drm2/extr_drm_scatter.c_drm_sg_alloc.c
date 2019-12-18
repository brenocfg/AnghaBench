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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  size_t vm_pindex_t ;
struct drm_sg_mem {int pages; scalar_t__ vaddr; struct drm_sg_mem* busaddr; } ;
struct drm_scatter_gather {scalar_t__ handle; int /*<<< orphan*/  size; } ;
struct drm_device {struct drm_sg_mem* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_SG ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int /*<<< orphan*/  DRM_MEM_SGLISTS ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IDX_TO_OFF (size_t) ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_vmalloc_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct drm_sg_mem*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 struct drm_sg_mem vtophys (scalar_t__) ; 

int drm_sg_alloc(struct drm_device *dev, struct drm_scatter_gather * request)
{
	struct drm_sg_mem *entry;
	vm_size_t size;
	vm_pindex_t pindex;

	DRM_DEBUG("\n");

	if (!drm_core_check_feature(dev, DRIVER_SG))
		return -EINVAL;

	if (dev->sg)
		return -EINVAL;

	entry = malloc(sizeof(*entry), DRM_MEM_DRIVER, M_NOWAIT | M_ZERO);
	if (!entry)
		return -ENOMEM;

	DRM_DEBUG("request size=%ld\n", request->size);

	size = round_page(request->size);
	entry->pages = atop(size);
	entry->busaddr = malloc(entry->pages * sizeof(*entry->busaddr),
	    DRM_MEM_SGLISTS, M_NOWAIT | M_ZERO);
	if (!entry->busaddr) {
		free(entry, DRM_MEM_DRIVER);
		return -ENOMEM;
	}

	entry->vaddr = drm_vmalloc_dma(size);
	if (entry->vaddr == 0) {
		free(entry->busaddr, DRM_MEM_DRIVER);
		free(entry, DRM_MEM_DRIVER);
		return -ENOMEM;
	}

	for (pindex = 0; pindex < entry->pages; pindex++) {
		entry->busaddr[pindex] =
		    vtophys(entry->vaddr + IDX_TO_OFF(pindex));
	}

	request->handle = entry->vaddr;

	dev->sg = entry;

	DRM_DEBUG("allocated %ju pages @ 0x%08zx, contents=%08lx\n",
	    entry->pages, entry->vaddr, *(unsigned long *)entry->vaddr);

	return 0;
}