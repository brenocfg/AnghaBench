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
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_3__ {int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_b; } ;
typedef  TYPE_1__ qla_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ql_free_dmabuf(qla_host_t *ha, qla_dma_t *dma_buf)
{
	bus_dmamap_unload(dma_buf->dma_tag, dma_buf->dma_map); 
        bus_dmamem_free(dma_buf->dma_tag, dma_buf->dma_b, dma_buf->dma_map);
        bus_dma_tag_destroy(dma_buf->dma_tag);
}