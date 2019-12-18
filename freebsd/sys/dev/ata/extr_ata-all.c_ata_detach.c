#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;
struct ata_channel {int flags; int /*<<< orphan*/  state_mtx; TYPE_1__ dma; int /*<<< orphan*/ * r_irq; int /*<<< orphan*/  ih; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/  conntask; int /*<<< orphan*/  poll_callout; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  ATA_IRQ_RID ; 
 int ATA_PERIODIC_POLL ; 
 int /*<<< orphan*/  ATA_STALL_QUEUE ; 
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

int
ata_detach(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    /* check that we have a valid channel to detach */
    if (!ch->r_irq)
	return ENXIO;

    /* grap the channel lock so no new requests gets launched */
    mtx_lock(&ch->state_mtx);
    ch->state |= ATA_STALL_QUEUE;
    mtx_unlock(&ch->state_mtx);
    if (ch->flags & ATA_PERIODIC_POLL)
	callout_drain(&ch->poll_callout);

    taskqueue_drain(taskqueue_thread, &ch->conntask);

	mtx_lock(&ch->state_mtx);
	xpt_async(AC_LOST_DEVICE, ch->path, NULL);
	xpt_free_path(ch->path);
	xpt_bus_deregister(cam_sim_path(ch->sim));
	cam_sim_free(ch->sim, /*free_devq*/TRUE);
	ch->sim = NULL;
	mtx_unlock(&ch->state_mtx);

    /* release resources */
    bus_teardown_intr(dev, ch->r_irq, ch->ih);
    bus_release_resource(dev, SYS_RES_IRQ, ATA_IRQ_RID, ch->r_irq);
    ch->r_irq = NULL;

    /* free DMA resources if DMA HW present*/
    if (ch->dma.free)
	ch->dma.free(dev);

    mtx_destroy(&ch->state_mtx);
    return 0;
}