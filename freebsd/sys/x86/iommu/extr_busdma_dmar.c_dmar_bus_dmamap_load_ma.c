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
struct vm_page {int dummy; } ;
struct bus_dmamap_dmar {int dummy; } ;
struct bus_dma_tag_dmar {int dummy; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  scalar_t__ bus_dmamap_t ;
typedef  scalar_t__ bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int dmar_bus_dmamap_load_something (struct bus_dma_tag_dmar*,struct bus_dmamap_dmar*,struct vm_page**,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
dmar_bus_dmamap_load_ma(bus_dma_tag_t dmat, bus_dmamap_t map1,
    struct vm_page **ma, bus_size_t tlen, int ma_offs, int flags,
    bus_dma_segment_t *segs, int *segp)
{
	struct bus_dma_tag_dmar *tag;
	struct bus_dmamap_dmar *map;

	tag = (struct bus_dma_tag_dmar *)dmat;
	map = (struct bus_dmamap_dmar *)map1;
	return (dmar_bus_dmamap_load_something(tag, map, ma, ma_offs, tlen,
	    flags, segs, segp));
}