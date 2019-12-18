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
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_3__ {scalar_t__ dt_maxsize; scalar_t__ dt_alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  contigfree (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nexus_dmamem_free(bus_dma_tag_t dmat, void *vaddr, bus_dmamap_t map)
{

	if (dmat->dt_maxsize <= PAGE_SIZE &&
	    dmat->dt_alignment < dmat->dt_maxsize)
		free(vaddr, M_DEVBUF);
	else
		contigfree(vaddr, dmat->dt_maxsize, M_DEVBUF);
}