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
typedef  int bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  int bus_addr_t ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int BUSDMA_DCACHE_MASK ; 
 int DMAMAP_COHERENT ; 
 int DMAMAP_DMAMEM_ALLOC ; 
 int DMAMAP_MBUF ; 

__attribute__((used)) static __inline int
cacheline_bounce(bus_dmamap_t map, bus_addr_t addr, bus_size_t size)
{

	if (map->flags & (DMAMAP_DMAMEM_ALLOC | DMAMAP_COHERENT | DMAMAP_MBUF))
		return (0);
	return ((addr | size) & BUSDMA_DCACHE_MASK);
}