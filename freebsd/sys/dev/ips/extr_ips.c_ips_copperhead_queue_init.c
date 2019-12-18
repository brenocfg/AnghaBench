#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* copper_queue; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  ips_copper_queue_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_8__ {int nextstatus; scalar_t__ base_phys_addr; int /*<<< orphan*/ * status; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  COPPER_REG_SQER ; 
 int /*<<< orphan*/  COPPER_REG_SQHR ; 
 int /*<<< orphan*/  COPPER_REG_SQSR ; 
 int /*<<< orphan*/  COPPER_REG_SQTR ; 
 int ENOMEM ; 
 int IPS_MAX_CMD_NUM ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ips_copperhead_queue_callback ; 
 int /*<<< orphan*/  ips_write_4 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ips_copperhead_queue_init(ips_softc_t *sc)
{
	int error;
	bus_dma_tag_t dmatag;
	bus_dmamap_t dmamap;
       	if (bus_dma_tag_create(	/* parent    */	sc->adapter_dmatag,
				/* alignemnt */	1,
				/* boundary  */	0,
				/* lowaddr   */	BUS_SPACE_MAXADDR_32BIT,
				/* highaddr  */	BUS_SPACE_MAXADDR,
				/* filter    */	NULL,
				/* filterarg */	NULL,
				/* maxsize   */	sizeof(ips_copper_queue_t),
				/* numsegs   */	1,
				/* maxsegsize*/	sizeof(ips_copper_queue_t),
				/* flags     */	0,
				/* lockfunc  */ NULL,
				/* lockarg   */ NULL,
				&dmatag) != 0) {
                device_printf(sc->dev, "can't alloc dma tag for statue queue\n");
		error = ENOMEM;
		return error;
        }
	if(bus_dmamem_alloc(dmatag, (void *)&(sc->copper_queue), 
	   		    BUS_DMA_NOWAIT, &dmamap)){
		error = ENOMEM;
		goto exit;
	}
	bzero(sc->copper_queue, sizeof(ips_copper_queue_t));
	sc->copper_queue->dmatag = dmatag;
	sc->copper_queue->dmamap = dmamap;
	sc->copper_queue->nextstatus = 1;
	bus_dmamap_load(dmatag, dmamap, 
			&(sc->copper_queue->status[0]), IPS_MAX_CMD_NUM * 4, 
			ips_copperhead_queue_callback, sc->copper_queue, 
			BUS_DMA_NOWAIT);
	if(sc->copper_queue->base_phys_addr == 0){
		error = ENOMEM;
		goto exit;
	}
	ips_write_4(sc, COPPER_REG_SQSR, sc->copper_queue->base_phys_addr);
	ips_write_4(sc, COPPER_REG_SQER, sc->copper_queue->base_phys_addr + 
		    IPS_MAX_CMD_NUM * 4);
	ips_write_4(sc, COPPER_REG_SQHR, sc->copper_queue->base_phys_addr + 4);
	ips_write_4(sc, COPPER_REG_SQTR, sc->copper_queue->base_phys_addr);

	
	return 0;
exit:
	if (sc->copper_queue != NULL)
		bus_dmamem_free(dmatag, sc->copper_queue, dmamap);
	bus_dma_tag_destroy(dmatag);
	return error;
}