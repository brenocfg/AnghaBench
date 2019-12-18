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
struct hyperv_dma {int /*<<< orphan*/  hv_dtag; int /*<<< orphan*/  hv_dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
hyperv_dmamem_free(struct hyperv_dma *dma, void *ptr)
{
	bus_dmamap_unload(dma->hv_dtag, dma->hv_dmap);
	bus_dmamem_free(dma->hv_dtag, ptr, dma->hv_dmap);
	bus_dma_tag_destroy(dma->hv_dtag);
}