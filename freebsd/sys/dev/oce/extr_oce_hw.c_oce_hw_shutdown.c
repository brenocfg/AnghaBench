#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bsmbx; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  bmbx_lock; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_delete_nw_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_dma_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_free_lro (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_fw_clean (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_hw_intr_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_hw_pci_free (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_intr_free (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_queue_release_all (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_stats_free (TYPE_1__*) ; 

void
oce_hw_shutdown(POCE_SOFTC sc)
{

	oce_stats_free(sc);
	/* disable hardware interrupts */
	oce_hw_intr_disable(sc);
#if defined(INET6) || defined(INET)
	/* Free LRO resources */
	oce_free_lro(sc);
#endif
	/* Release queue*/
	oce_queue_release_all(sc);
	/*Delete Network Interface*/
	oce_delete_nw_interface(sc);
	/* After fw clean we dont send any cmds to fw.*/
	oce_fw_clean(sc);
	/* release intr resources */
	oce_intr_free(sc);
	/* release PCI resources */
	oce_hw_pci_free(sc);
	/* free mbox specific resources */
	LOCK_DESTROY(&sc->bmbx_lock);
	LOCK_DESTROY(&sc->dev_lock);

	oce_dma_free(sc, &sc->bsmbx);
}