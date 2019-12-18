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
struct mlx_softc {int /*<<< orphan*/  mlx_io_lock; int /*<<< orphan*/  mlx_config_lock; int /*<<< orphan*/ * mlx_enq2; int /*<<< orphan*/ * mlx_mem; int /*<<< orphan*/  mlx_mem_rid; int /*<<< orphan*/  mlx_mem_type; int /*<<< orphan*/  mlx_dev; scalar_t__ mlx_parent_dmat; int /*<<< orphan*/ * mlx_irq; scalar_t__ mlx_sg_dmat; int /*<<< orphan*/  mlx_sg_dmamap; scalar_t__ mlx_sgtable; scalar_t__ mlx_sgbusaddr; scalar_t__ mlx_buffer_dmat; int /*<<< orphan*/  mlx_timeout; int /*<<< orphan*/  mlx_freecmds; scalar_t__ mlx_intr; int /*<<< orphan*/ * mlx_dev_t; } ;
struct mlx_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct mlx_command* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mlx_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_link ; 
 int /*<<< orphan*/  mlx_freecmd (struct mlx_command*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void
mlx_free(struct mlx_softc *sc)
{
    struct mlx_command	*mc;

    debug_called(1);

    /* destroy control device */
    if (sc->mlx_dev_t != NULL)
	destroy_dev(sc->mlx_dev_t);

    if (sc->mlx_intr)
	bus_teardown_intr(sc->mlx_dev, sc->mlx_irq, sc->mlx_intr);

    /* cancel status timeout */
    MLX_IO_LOCK(sc);
    callout_stop(&sc->mlx_timeout);

    /* throw away any command buffers */
    while ((mc = TAILQ_FIRST(&sc->mlx_freecmds)) != NULL) {
	TAILQ_REMOVE(&sc->mlx_freecmds, mc, mc_link);
	mlx_freecmd(mc);
    }
    MLX_IO_UNLOCK(sc);
    callout_drain(&sc->mlx_timeout);

    /* destroy data-transfer DMA tag */
    if (sc->mlx_buffer_dmat)
	bus_dma_tag_destroy(sc->mlx_buffer_dmat);

    /* free and destroy DMA memory and tag for s/g lists */
    if (sc->mlx_sgbusaddr)
	bus_dmamap_unload(sc->mlx_sg_dmat, sc->mlx_sg_dmamap);
    if (sc->mlx_sgtable)
	bus_dmamem_free(sc->mlx_sg_dmat, sc->mlx_sgtable, sc->mlx_sg_dmamap);
    if (sc->mlx_sg_dmat)
	bus_dma_tag_destroy(sc->mlx_sg_dmat);

    /* disconnect the interrupt handler */
    if (sc->mlx_irq != NULL)
	bus_release_resource(sc->mlx_dev, SYS_RES_IRQ, 0, sc->mlx_irq);

    /* destroy the parent DMA tag */
    if (sc->mlx_parent_dmat)
	bus_dma_tag_destroy(sc->mlx_parent_dmat);

    /* release the register window mapping */
    if (sc->mlx_mem != NULL)
	bus_release_resource(sc->mlx_dev, sc->mlx_mem_type, sc->mlx_mem_rid, sc->mlx_mem);

    /* free controller enquiry data */
    if (sc->mlx_enq2 != NULL)
	free(sc->mlx_enq2, M_DEVBUF);

    sx_destroy(&sc->mlx_config_lock);
    mtx_destroy(&sc->mlx_io_lock);
}