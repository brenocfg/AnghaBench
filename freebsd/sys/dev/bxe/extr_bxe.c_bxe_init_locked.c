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
typedef  scalar_t__ uint8_t ;
struct bxe_softc {scalar_t__ state; scalar_t__ recovery_state; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_CORE_LOCK_ASSERT (struct bxe_softc*) ; 
 scalar_t__ BXE_RECOVERY_DONE ; 
 scalar_t__ BXE_RECOVERY_FAILED ; 
 scalar_t__ BXE_STATE_ERROR ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int ENXIO ; 
 scalar_t__ FALSE ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ IS_PF (struct bxe_softc*) ; 
 int /*<<< orphan*/  LOAD_OPEN ; 
 int /*<<< orphan*/  PCI_PM_D0 ; 
 int /*<<< orphan*/  PCI_PM_D3hot ; 
 int SC_PATH (struct bxe_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bxe_chk_parity_attn (struct bxe_softc*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bxe_get_load_status (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_leader_reset (struct bxe_softc*) ; 
 int bxe_nic_load (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_reset_is_done (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_set_power_state (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_set_reset_global (struct bxe_softc*) ; 
 scalar_t__ bxe_trylock_leader_lock (struct bxe_softc*) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bxe_init_locked(struct bxe_softc *sc)
{
    int other_engine = SC_PATH(sc) ? 0 : 1;
    uint8_t other_load_status, load_status;
    uint8_t global = FALSE;
    int rc;

    BXE_CORE_LOCK_ASSERT(sc);

    /* check if the driver is already running */
    if (if_getdrvflags(sc->ifp) & IFF_DRV_RUNNING) {
        BLOGD(sc, DBG_LOAD, "Init called while driver is running!\n");
        return (0);
    }

    if((sc->state == BXE_STATE_ERROR) &&
        (sc->recovery_state == BXE_RECOVERY_FAILED)) {
        BLOGE(sc, "Initialization not done, "
                  "as previous recovery failed."
                  "Reboot/Power-cycle the system\n" );
        return (ENXIO);
    }


    bxe_set_power_state(sc, PCI_PM_D0);

    /*
     * If parity occurred during the unload, then attentions and/or
     * RECOVERY_IN_PROGRES may still be set. If so we want the first function
     * loaded on the current engine to complete the recovery. Parity recovery
     * is only relevant for PF driver.
     */
    if (IS_PF(sc)) {
        other_load_status = bxe_get_load_status(sc, other_engine);
        load_status = bxe_get_load_status(sc, SC_PATH(sc));

        if (!bxe_reset_is_done(sc, SC_PATH(sc)) ||
            bxe_chk_parity_attn(sc, &global, TRUE)) {
            do {
                /*
                 * If there are attentions and they are in global blocks, set
                 * the GLOBAL_RESET bit regardless whether it will be this
                 * function that will complete the recovery or not.
                 */
                if (global) {
                    bxe_set_reset_global(sc);
                }

                /*
                 * Only the first function on the current engine should try
                 * to recover in open. In case of attentions in global blocks
                 * only the first in the chip should try to recover.
                 */
                if ((!load_status && (!global || !other_load_status)) &&
                    bxe_trylock_leader_lock(sc) && !bxe_leader_reset(sc)) {
                    BLOGI(sc, "Recovered during init\n");
                    break;
                }

                /* recovery has failed... */
                bxe_set_power_state(sc, PCI_PM_D3hot);
                sc->recovery_state = BXE_RECOVERY_FAILED;

                BLOGE(sc, "Recovery flow hasn't properly "
                          "completed yet, try again later. "
                          "If you still see this message after a "
                          "few retries then power cycle is required.\n");

                rc = ENXIO;
                goto bxe_init_locked_done;
            } while (0);
        }
    }

    sc->recovery_state = BXE_RECOVERY_DONE;

    rc = bxe_nic_load(sc, LOAD_OPEN);

bxe_init_locked_done:

    if (rc) {
        /* Tell the stack the driver is NOT running! */
        BLOGE(sc, "Initialization failed, "
                  "stack notified driver is NOT running!\n");
	if_setdrvflagbits(sc->ifp, 0, IFF_DRV_RUNNING);
    }

    return (rc);
}