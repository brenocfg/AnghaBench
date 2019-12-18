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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  int vm_offset_t ;
struct vm_page {int dummy; } ;
struct bus_dmamap_dmar {scalar_t__ cansleep; } ;
struct bus_dma_tag_dmar {int dummy; } ;
typedef  scalar_t__ pmap_t ;
typedef  int bus_size_t ;
typedef  scalar_t__ bus_dmamap_t ;
typedef  scalar_t__ bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OFF_TO_IDX (scalar_t__) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 int dmar_bus_dmamap_load_something (struct bus_dma_tag_dmar*,struct bus_dmamap_dmar*,int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmap_extract (scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_kextract (scalar_t__) ; 
 scalar_t__ round_page (int) ; 
 scalar_t__ trunc_page (int) ; 
 int /*<<< orphan*/  vm_page_initfake (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmar_bus_dmamap_load_buffer(bus_dma_tag_t dmat, bus_dmamap_t map1, void *buf,
    bus_size_t buflen, pmap_t pmap, int flags, bus_dma_segment_t *segs,
    int *segp)
{
	struct bus_dma_tag_dmar *tag;
	struct bus_dmamap_dmar *map;
	vm_page_t *ma, fma;
	vm_paddr_t pstart, pend, paddr;
	int error, i, ma_cnt, mflags, offset;

	tag = (struct bus_dma_tag_dmar *)dmat;
	map = (struct bus_dmamap_dmar *)map1;
	pstart = trunc_page((vm_offset_t)buf);
	pend = round_page((vm_offset_t)buf + buflen);
	offset = (vm_offset_t)buf & PAGE_MASK;
	ma_cnt = OFF_TO_IDX(pend - pstart);
	mflags = map->cansleep ? M_WAITOK : M_NOWAIT;
	ma = malloc(sizeof(vm_page_t) * ma_cnt, M_DEVBUF, mflags);
	if (ma == NULL)
		return (ENOMEM);
	fma = NULL;
	for (i = 0; i < ma_cnt; i++, pstart += PAGE_SIZE) {
		if (pmap == kernel_pmap)
			paddr = pmap_kextract(pstart);
		else
			paddr = pmap_extract(pmap, pstart);
		ma[i] = PHYS_TO_VM_PAGE(paddr);
		if (ma[i] == NULL || VM_PAGE_TO_PHYS(ma[i]) != paddr) {
			/*
			 * If PHYS_TO_VM_PAGE() returned NULL or the
			 * vm_page was not initialized we'll use a
			 * fake page.
			 */
			if (fma == NULL) {
				fma = malloc(sizeof(struct vm_page) * ma_cnt,
				    M_DEVBUF, M_ZERO | mflags);
				if (fma == NULL) {
					free(ma, M_DEVBUF);
					return (ENOMEM);
				}
			}
			vm_page_initfake(&fma[i], paddr, VM_MEMATTR_DEFAULT);
			ma[i] = &fma[i];
		}
	}
	error = dmar_bus_dmamap_load_something(tag, map, ma, offset, buflen,
	    flags, segs, segp);
	free(ma, M_DEVBUF);
	free(fma, M_DEVBUF);
	return (error);
}