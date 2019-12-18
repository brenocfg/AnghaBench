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
typedef  void* bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_3__ {uintptr_t alignment; scalar_t__ maxsize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  XXX ; 
 void* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bus_dmamem_alloc(bus_dma_tag_t dmat, void** vaddr, int flags,
    bus_dmamap_t *mapp)
{
	void *addr;

	addr = malloc(dmat->maxsize + dmat->alignment, XXX, XXX);
	if (addr == NULL)
		return (ENOMEM);

	*mapp = addr;
	addr = (void*)(((uintptr_t)addr + dmat->alignment - 1) & ~(dmat->alignment - 1));

	*vaddr = addr;
	return (0);
}