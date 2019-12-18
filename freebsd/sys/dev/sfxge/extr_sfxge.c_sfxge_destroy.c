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
struct sfxge_softc {int /*<<< orphan*/  task_reset; int /*<<< orphan*/  dev; int /*<<< orphan*/ * enp; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK_DESTROY (struct sfxge_softc*) ; 
 int /*<<< orphan*/  efx_nic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_nic_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_nic_unprobe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_nvram_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_vpd_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_bar_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_dma_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_ev_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_intr_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_mcdi_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_port_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_rx_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_tx_fini (struct sfxge_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
sfxge_destroy(struct sfxge_softc *sc)
{
	efx_nic_t *enp;

	/* Clean up transmit state. */
	sfxge_tx_fini(sc);

	/* Clean up receive state. */
	sfxge_rx_fini(sc);

	/* Clean up port state. */
	sfxge_port_fini(sc);

	/* Clean up event processing state. */
	sfxge_ev_fini(sc);

	/* Clean up interrupts. */
	sfxge_intr_fini(sc);

	/* Tear down common code subsystems. */
	efx_nic_reset(sc->enp);
	efx_vpd_fini(sc->enp);
	efx_nvram_fini(sc->enp);
	efx_nic_unprobe(sc->enp);

	/* Tear down MCDI. */
	sfxge_mcdi_fini(sc);

	/* Destroy common code context. */
	enp = sc->enp;
	sc->enp = NULL;
	efx_nic_destroy(enp);

	/* Free DMA memory. */
	sfxge_dma_fini(sc);

	/* Free mapped BARs. */
	sfxge_bar_fini(sc);

	(void) pci_disable_busmaster(sc->dev);

	taskqueue_drain(taskqueue_thread, &sc->task_reset);

	/* Destroy the softc lock. */
	SFXGE_ADAPTER_LOCK_DESTROY(sc);
}