#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct bounce_zone {int /*<<< orphan*/  active_bpages; int /*<<< orphan*/  reserved_bpages; int /*<<< orphan*/  bounce_page_list; } ;
struct bounce_page {int vaddr; int busaddr; int dataoffs; int /*<<< orphan*/  datacount; int /*<<< orphan*/  datapage; int /*<<< orphan*/  datavaddr; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  TYPE_2__* bus_dmamap_t ;
typedef  TYPE_3__* bus_dma_tag_t ;
typedef  int bus_addr_t ;
struct TYPE_6__ {int flags; } ;
struct TYPE_8__ {TYPE_1__ common; struct bounce_zone* bounce_zone; } ;
struct TYPE_7__ {int flags; scalar_t__ pagesneeded; scalar_t__ pagesreserved; int /*<<< orphan*/  bpages; } ;

/* Variables and functions */
 int BUS_DMA_KEEP_PG_OFFSET ; 
 int DMAMAP_COULD_BOUNCE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 struct bounce_page* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bounce_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bounce_lock ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static bus_addr_t
add_bounce_page(bus_dma_tag_t dmat, bus_dmamap_t map, vm_offset_t vaddr,
		bus_addr_t addr, bus_size_t size)
{
	struct bounce_zone *bz;
	struct bounce_page *bpage;

	KASSERT(dmat->bounce_zone != NULL, ("no bounce zone in dma tag"));
	KASSERT((map->flags & DMAMAP_COULD_BOUNCE) != 0,
	    ("add_bounce_page: bad map %p", map));

	bz = dmat->bounce_zone;
	if (map->pagesneeded == 0)
		panic("add_bounce_page: map doesn't need any pages");
	map->pagesneeded--;

	if (map->pagesreserved == 0)
		panic("add_bounce_page: map doesn't need any pages");
	map->pagesreserved--;

	mtx_lock(&bounce_lock);
	bpage = STAILQ_FIRST(&bz->bounce_page_list);
	if (bpage == NULL)
		panic("add_bounce_page: free page list is empty");

	STAILQ_REMOVE_HEAD(&bz->bounce_page_list, links);
	bz->reserved_bpages--;
	bz->active_bpages++;
	mtx_unlock(&bounce_lock);

	if (dmat->common.flags & BUS_DMA_KEEP_PG_OFFSET) {
		/* Page offset needs to be preserved. */
		bpage->vaddr |= addr & PAGE_MASK;
		bpage->busaddr |= addr & PAGE_MASK;
	}
	bpage->datavaddr = vaddr;
	bpage->datapage = PHYS_TO_VM_PAGE(addr);
	bpage->dataoffs = addr & PAGE_MASK;
	bpage->datacount = size;
	STAILQ_INSERT_TAIL(&(map->bpages), bpage, links);
	return (bpage->busaddr);
}