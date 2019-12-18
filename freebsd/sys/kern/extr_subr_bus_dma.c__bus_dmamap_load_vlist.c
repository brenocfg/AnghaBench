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
struct pmap {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_3__ {size_t ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int _bus_dmamap_load_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,struct pmap*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
_bus_dmamap_load_vlist(bus_dma_tag_t dmat, bus_dmamap_t map,
    bus_dma_segment_t *list, int sglist_cnt, struct pmap *pmap, int *nsegs,
    int flags, size_t offset, size_t length)
{
	int error;

	error = 0;
	for (; sglist_cnt > 0 && length != 0; sglist_cnt--, list++) {
		char *addr;
		size_t ds_len;

		KASSERT((offset < list->ds_len),
		    ("Invalid mid-segment offset"));
		addr = (char *)(uintptr_t)list->ds_addr + offset;
		ds_len = list->ds_len - offset;
		offset = 0;
		if (ds_len > length)
			ds_len = length;
		length -= ds_len;
		KASSERT((ds_len != 0), ("Segment length is zero"));
		error = _bus_dmamap_load_buffer(dmat, map, addr, ds_len, pmap,
		    flags, NULL, nsegs);
		if (error)
			break;
	}
	return (error);
}