#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_5__ {TYPE_3__* q; } ;
struct TYPE_4__ {TYPE_3__* q; } ;
struct tws_softc {int obfl_q_overrun; int irqs; scalar_t__ intr_type; int /*<<< orphan*/  tws_clist; int /*<<< orphan*/  tws_cdev; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  gen_lock; int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  q_lock; TYPE_2__ trace_q; TYPE_1__ aen_q; scalar_t__ data_tag; int /*<<< orphan*/  ioctl_data_map; scalar_t__ ioctl_data_mem; TYPE_3__* scan_ccb; TYPE_3__* sense_bufs; TYPE_3__* reqs; int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  reg_res_id; scalar_t__ reg_res; int /*<<< orphan*/  tws_dev; int /*<<< orphan*/  mfa_res_id; scalar_t__ mfa_res; scalar_t__ cmd_tag; int /*<<< orphan*/  cmd_map; scalar_t__ dma_mem; scalar_t__ dma_mem_phys; int /*<<< orphan*/ * irq_res_id; scalar_t__* irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; scalar_t__ dma_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TWS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TWS_I2O0_HIMASK ; 
 int /*<<< orphan*/  TWS_I2O0_HOBDBC ; 
 scalar_t__ TWS_MSI ; 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWS_UNINIT_START ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct tws_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_cam_detach (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_init_connect (struct tws_softc*,int) ; 
 int tws_queue_depth ; 
 int /*<<< orphan*/  tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tws_send_event (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_teardown_intr (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_turn_off_interrupts (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_write_reg (struct tws_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tws_detach(device_t dev)
{
    struct tws_softc *sc = device_get_softc(dev);
    int i;
    u_int32_t reg;

    TWS_TRACE_DEBUG(sc, "entry", 0, 0);

    mtx_lock(&sc->gen_lock);
    tws_send_event(sc, TWS_UNINIT_START);
    mtx_unlock(&sc->gen_lock);

    /* needs to disable interrupt before detaching from cam */
    tws_turn_off_interrupts(sc);
    /* clear door bell */
    tws_write_reg(sc, TWS_I2O0_HOBDBC, ~0, 4);
    reg = tws_read_reg(sc, TWS_I2O0_HIMASK, 4);
    TWS_TRACE_DEBUG(sc, "turn-off-intr", reg, 0);
    sc->obfl_q_overrun = false;
    tws_init_connect(sc, 1);

    /* Teardown the state in our softc created in our attach routine. */
    /* Disconnect the interrupt handler. */
    tws_teardown_intr(sc);

    /* Release irq resource */
    for(i=0;i<sc->irqs;i++) {
        if ( sc->irq_res[i] ){
            if (bus_release_resource(sc->tws_dev,
                     SYS_RES_IRQ, sc->irq_res_id[i], sc->irq_res[i]))
                TWS_TRACE(sc, "bus release irq resource", 
                                       i, sc->irq_res_id[i]);
        }
    }
    if ( sc->intr_type == TWS_MSI ) {
        pci_release_msi(sc->tws_dev);
    }

    tws_cam_detach(sc);

    if (sc->dma_mem_phys)
	    bus_dmamap_unload(sc->cmd_tag, sc->cmd_map);
    if (sc->dma_mem)
	    bus_dmamem_free(sc->cmd_tag, sc->dma_mem, sc->cmd_map);
    if (sc->cmd_tag)
	    bus_dma_tag_destroy(sc->cmd_tag);

    /* Release memory resource */
    if ( sc->mfa_res ){
        if (bus_release_resource(sc->tws_dev,
                 SYS_RES_MEMORY, sc->mfa_res_id, sc->mfa_res))
            TWS_TRACE(sc, "bus release mem resource", 0, sc->mfa_res_id);
    }
    if ( sc->reg_res ){
        if (bus_release_resource(sc->tws_dev,
                 SYS_RES_MEMORY, sc->reg_res_id, sc->reg_res))
            TWS_TRACE(sc, "bus release mem resource", 0, sc->reg_res_id);
    }

    for ( i=0; i< tws_queue_depth; i++) {
	    if (sc->reqs[i].dma_map)
		    bus_dmamap_destroy(sc->data_tag, sc->reqs[i].dma_map);
	    callout_drain(&sc->reqs[i].timeout);
    }

    callout_drain(&sc->stats_timer);
    free(sc->reqs, M_TWS);
    free(sc->sense_bufs, M_TWS);
    free(sc->scan_ccb, M_TWS);
    if (sc->ioctl_data_mem)
            bus_dmamem_free(sc->data_tag, sc->ioctl_data_mem, sc->ioctl_data_map);
    if (sc->data_tag)
	    bus_dma_tag_destroy(sc->data_tag);
    free(sc->aen_q.q, M_TWS);
    free(sc->trace_q.q, M_TWS);
    mtx_destroy(&sc->q_lock);
    mtx_destroy(&sc->sim_lock);
    mtx_destroy(&sc->gen_lock);
    mtx_destroy(&sc->io_lock);
    destroy_dev(sc->tws_cdev);
    sysctl_ctx_free(&sc->tws_clist);
    return (0);
}