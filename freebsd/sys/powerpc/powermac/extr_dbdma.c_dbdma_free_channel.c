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
struct TYPE_5__ {int /*<<< orphan*/  sc_dmatag; int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/  sc_slots; } ;
typedef  TYPE_1__ dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DBDMA ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
dbdma_free_channel(dbdma_channel_t *chan)
{

	dbdma_stop(chan);

	bus_dmamem_free(chan->sc_dmatag, chan->sc_slots, chan->sc_dmamap);
	bus_dma_tag_destroy(chan->sc_dmatag);

	free(chan, M_DBDMA);

	return (0);
}