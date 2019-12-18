#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  psim; int /*<<< orphan*/  ppath; int /*<<< orphan*/  irq; int /*<<< orphan*/  ih; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/  sense_dmat; int /*<<< orphan*/  sense_dmamap; int /*<<< orphan*/  sense_buffers; int /*<<< orphan*/  srb_dmat; int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  pFreeSRB; int /*<<< orphan*/  sg_dmat; int /*<<< orphan*/  iores; } ;
typedef  TYPE_1__* PACB ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_destroySRB (TYPE_1__*) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
trm_detach(device_t dev)
{
	PACB pACB = device_get_softc(dev);

	bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(0), pACB->iores);
	trm_destroySRB(pACB);
	bus_dma_tag_destroy(pACB->sg_dmat);
	bus_dmamap_unload(pACB->srb_dmat, pACB->srb_dmamap);
	bus_dmamem_free(pACB->srb_dmat, pACB->pFreeSRB,
	    pACB->srb_dmamap);
	bus_dma_tag_destroy(pACB->srb_dmat);	
	bus_dmamap_unload(pACB->sense_dmat, pACB->sense_dmamap);
	bus_dmamem_free(pACB->sense_dmat, pACB->sense_buffers,
	    pACB->sense_dmamap);
	bus_dma_tag_destroy(pACB->sense_dmat);				      
	bus_dma_tag_destroy(pACB->buffer_dmat);
	bus_teardown_intr(dev, pACB->irq, pACB->ih);
	bus_release_resource(dev, SYS_RES_IRQ, 0, pACB->irq);
	xpt_async(AC_LOST_DEVICE, pACB->ppath, NULL);
	xpt_free_path(pACB->ppath);
	xpt_bus_deregister(cam_sim_path(pACB->psim));
	cam_sim_free(pACB->psim, TRUE);
	return (0);
}