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
struct twe_softc {int /*<<< orphan*/  twe_io_lock; int /*<<< orphan*/  twe_config_lock; struct cdev* twe_dev_t; int /*<<< orphan*/ * twe_io; int /*<<< orphan*/  twe_dev; scalar_t__ twe_parent_dmat; int /*<<< orphan*/ * twe_irq; scalar_t__ twe_intr; scalar_t__ twe_buffer_dmat; scalar_t__ twe_immediate_dmat; int /*<<< orphan*/  twe_immediate_map; int /*<<< orphan*/ * twe_immediate; int /*<<< orphan*/  twe_cmdmap; int /*<<< orphan*/ * twe_cmd; scalar_t__ twe_cmd_dmat; } ;
struct twe_request {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TWE_IO_CONFIG_REG ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 struct twe_request* twe_dequeue_free (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_free_request (struct twe_request*) ; 

__attribute__((used)) static void
twe_free(struct twe_softc *sc)
{
    struct twe_request	*tr;

    debug_called(4);

    /* throw away any command buffers */
    while ((tr = twe_dequeue_free(sc)) != NULL)
	twe_free_request(tr);

    if (sc->twe_cmd != NULL) {
	bus_dmamap_unload(sc->twe_cmd_dmat, sc->twe_cmdmap);
	bus_dmamem_free(sc->twe_cmd_dmat, sc->twe_cmd, sc->twe_cmdmap);
    }

    if (sc->twe_immediate != NULL) {
	bus_dmamap_unload(sc->twe_immediate_dmat, sc->twe_immediate_map);
	bus_dmamem_free(sc->twe_immediate_dmat, sc->twe_immediate,
			sc->twe_immediate_map);
    }

    if (sc->twe_immediate_dmat)
	bus_dma_tag_destroy(sc->twe_immediate_dmat);

    /* destroy the data-transfer DMA tag */
    if (sc->twe_buffer_dmat)
	bus_dma_tag_destroy(sc->twe_buffer_dmat);

    /* disconnect the interrupt handler */
    if (sc->twe_intr)
	bus_teardown_intr(sc->twe_dev, sc->twe_irq, sc->twe_intr);
    if (sc->twe_irq != NULL)
	bus_release_resource(sc->twe_dev, SYS_RES_IRQ, 0, sc->twe_irq);

    /* destroy the parent DMA tag */
    if (sc->twe_parent_dmat)
	bus_dma_tag_destroy(sc->twe_parent_dmat);

    /* release the register window mapping */
    if (sc->twe_io != NULL)
	bus_release_resource(sc->twe_dev, SYS_RES_IOPORT, TWE_IO_CONFIG_REG, sc->twe_io);

    /* destroy control device */
    if (sc->twe_dev_t != (struct cdev *)NULL)
	destroy_dev(sc->twe_dev_t);

    sx_destroy(&sc->twe_config_lock);
    mtx_destroy(&sc->twe_io_lock);
}