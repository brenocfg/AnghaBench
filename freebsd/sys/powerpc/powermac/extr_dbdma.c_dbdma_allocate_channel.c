#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct dbdma_channel {int dummy; } ;
struct TYPE_7__ {int sc_nslots; int /*<<< orphan*/  sc_slots; int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/  sc_dmatag; scalar_t__ sc_slots_pa; int /*<<< orphan*/  sc_off; struct resource* sc_regs; } ;
typedef  TYPE_1__ dbdma_channel_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CHAN_CMDPTR_HI ; 
 int /*<<< orphan*/  M_DBDMA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbdma_phys_callback ; 
 int /*<<< orphan*/  dbdma_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  dbdma_write_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 

int
dbdma_allocate_channel(struct resource *dbdma_regs, u_int offset,
    bus_dma_tag_t parent_dma, int slots, dbdma_channel_t **chan)
{
	int error = 0;
	dbdma_channel_t *channel;

	channel = *chan = malloc(sizeof(struct dbdma_channel), M_DBDMA, 
	    M_WAITOK | M_ZERO);

	channel->sc_regs = dbdma_regs;
	channel->sc_off = offset;
	dbdma_stop(channel);

	channel->sc_slots_pa = 0;

	error = bus_dma_tag_create(parent_dma, 16, 0, BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR, NULL, NULL, PAGE_SIZE, 1, PAGE_SIZE, 0, NULL,
	    NULL, &(channel->sc_dmatag));

	error = bus_dmamem_alloc(channel->sc_dmatag,
	    (void **)&channel->sc_slots, BUS_DMA_WAITOK | BUS_DMA_ZERO,
	    &channel->sc_dmamap);

	error = bus_dmamap_load(channel->sc_dmatag, channel->sc_dmamap,
	    channel->sc_slots, PAGE_SIZE, dbdma_phys_callback, channel, 0);

	dbdma_write_reg(channel, CHAN_CMDPTR_HI, 0);

	channel->sc_nslots = slots;

	return (error);
}