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
struct bxe_softc {scalar_t__ state; int /*<<< orphan*/ * ifp; int /*<<< orphan*/  ifmedia; int /*<<< orphan*/  sp_err_timeout_task; int /*<<< orphan*/ * chip_tq; int /*<<< orphan*/  chip_tq_task; int /*<<< orphan*/  chip_tq_flags; } ;
typedef  int /*<<< orphan*/ * if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_CORE_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_CORE_UNLOCK (struct bxe_softc*) ; 
 scalar_t__ BXE_STATE_CLOSED ; 
 scalar_t__ BXE_STATE_DISABLED ; 
 int /*<<< orphan*/  CHIP_TQ_NONE ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int EBUSY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNLOAD_CLOSE ; 
 int /*<<< orphan*/  atomic_store_rel_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_deallocate_bars (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_del_cdev (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_destroy_fp_mutexs (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_free_buf_rings (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_free_hsi_mem (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_free_ilt_mem (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_interrupt_free (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_nic_unload (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_periodic_stop (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_release_mutexes (struct bxe_softc*) ; 
 struct bxe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 scalar_t__ if_vlantrunkinuse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
bxe_detach(device_t dev)
{
    struct bxe_softc *sc;
    if_t ifp;

    sc = device_get_softc(dev);

    BLOGD(sc, DBG_LOAD, "Starting detach...\n");

    ifp = sc->ifp;
    if (ifp != NULL && if_vlantrunkinuse(ifp)) {
        BLOGE(sc, "Cannot detach while VLANs are in use.\n");
        return(EBUSY);
    }

    bxe_del_cdev(sc);

    /* stop the periodic callout */
    bxe_periodic_stop(sc);

    /* stop the chip taskqueue */
    atomic_store_rel_long(&sc->chip_tq_flags, CHIP_TQ_NONE);
    if (sc->chip_tq) {
        taskqueue_drain(sc->chip_tq, &sc->chip_tq_task);
        taskqueue_free(sc->chip_tq);
        sc->chip_tq = NULL;
        taskqueue_drain_timeout(taskqueue_thread,
            &sc->sp_err_timeout_task);
    }

    /* stop and reset the controller if it was open */
    if (sc->state != BXE_STATE_CLOSED) {
        BXE_CORE_LOCK(sc);
        bxe_nic_unload(sc, UNLOAD_CLOSE, TRUE);
        sc->state = BXE_STATE_DISABLED;
        BXE_CORE_UNLOCK(sc);
    }

    /* release the network interface */
    if (ifp != NULL) {
        ether_ifdetach(ifp);
    }
    ifmedia_removeall(&sc->ifmedia);

    /* XXX do the following based on driver state... */

    /* free the host hardware/software hsi structures */
    bxe_free_hsi_mem(sc);

    /* free ilt */
    bxe_free_ilt_mem(sc);

    bxe_free_buf_rings(sc);

    /* release the interrupts */
    bxe_interrupt_free(sc);

    /* Release the mutexes*/
    bxe_destroy_fp_mutexs(sc);
    bxe_release_mutexes(sc);


    /* Release the PCIe BAR mapped memory */
    bxe_deallocate_bars(sc);

    /* Release the FreeBSD interface. */
    if (sc->ifp != NULL) {
        if_free(sc->ifp);
    }

    pci_disable_busmaster(dev);

    return (0);
}