#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int u_int ;
struct sglist {TYPE_1__* sg_segs; } ;
struct agp_i810_softc {TYPE_2__* match; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_4__ {unsigned long long busdma_addr_mask_sz; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss_len; int /*<<< orphan*/  ss_paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sglist* sglist_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sglist_free (struct sglist*) ; 

int
agp_intel_gtt_map_memory(device_t dev, vm_page_t *pages, u_int num_entries,
    struct sglist **sg_list)
{
	struct agp_i810_softc *sc;
	struct sglist *sg;
	int i;
#if 0
	int error;
	bus_dma_tag_t dmat;
#endif

	if (*sg_list != NULL)
		return (0);
	sc = device_get_softc(dev);
	sg = sglist_alloc(num_entries, M_WAITOK /* XXXKIB */);
	for (i = 0; i < num_entries; i++) {
		sg->sg_segs[i].ss_paddr = VM_PAGE_TO_PHYS(pages[i]);
		sg->sg_segs[i].ss_len = PAGE_SIZE;
	}

#if 0
	error = bus_dma_tag_create(bus_get_dma_tag(dev),
	    1 /* alignment */, 0 /* boundary */,
	    1ULL << sc->match->busdma_addr_mask_sz /* lowaddr */,
	    BUS_SPACE_MAXADDR /* highaddr */,
            NULL /* filtfunc */, NULL /* filtfuncarg */,
	    BUS_SPACE_MAXADDR /* maxsize */,
	    BUS_SPACE_UNRESTRICTED /* nsegments */,
	    BUS_SPACE_MAXADDR /* maxsegsz */,
	    0 /* flags */, NULL /* lockfunc */, NULL /* lockfuncarg */,
	    &dmat);
	if (error != 0) {
		sglist_free(sg);
		return (error);
	}
	/* XXXKIB */
#endif
	*sg_list = sg;
	return (0);
}