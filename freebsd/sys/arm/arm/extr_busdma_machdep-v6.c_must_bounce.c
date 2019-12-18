#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_5__ {scalar_t__ lowaddr; scalar_t__ highaddr; scalar_t__ (* filter ) (int /*<<< orphan*/ ,scalar_t__) ;struct TYPE_5__* parent; int /*<<< orphan*/  filterarg; } ;

/* Variables and functions */
 scalar_t__ alignment_bounce (TYPE_1__*,scalar_t__) ; 
 scalar_t__ cacheline_bounce (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ exclusion_bounce (TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
must_bounce(bus_dma_tag_t dmat, bus_dmamap_t map, bus_addr_t paddr,
    bus_size_t size)
{

	if (cacheline_bounce(map, paddr, size))
		return (1);

	/*
	 *  The tag already contains ancestors' alignment restrictions so this
	 *  check doesn't need to be inside the loop.
	 */
	if (alignment_bounce(dmat, paddr))
		return (1);

	/*
	 * Even though each tag has an exclusion zone that is a superset of its
	 * own and all its ancestors' exclusions, the exclusion zone of each tag
	 * up the chain must be checked within the loop, because the busdma
	 * rules say the filter function is called only when the address lies
	 * within the low-highaddr range of the tag that filterfunc belongs to.
	 */
	while (dmat != NULL && exclusion_bounce(dmat)) {
		if ((paddr >= dmat->lowaddr && paddr <= dmat->highaddr) &&
		    (dmat->filter == NULL ||
		    dmat->filter(dmat->filterarg, paddr) != 0))
			return (1);
		dmat = dmat->parent;
	}

	return (0);
}