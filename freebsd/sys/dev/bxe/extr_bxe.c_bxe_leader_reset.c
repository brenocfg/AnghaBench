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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {scalar_t__ is_leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int /*<<< orphan*/  BXE_NOMCP (struct bxe_softc*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_LOAD_DONE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_LOAD_REQ ; 
 int /*<<< orphan*/  DRV_MSG_CODE_LOAD_REQ_WITH_LFA ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_DONE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON_CHIP ; 
 int /*<<< orphan*/  SC_PATH (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_clear_reset_global (struct bxe_softc*) ; 
 scalar_t__ bxe_fw_command (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bxe_process_kill (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  bxe_release_leader_lock (struct bxe_softc*) ; 
 scalar_t__ bxe_reset_is_global (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_set_reset_done (struct bxe_softc*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int
bxe_leader_reset(struct bxe_softc *sc)
{
    int rc = 0;
    uint8_t global = bxe_reset_is_global(sc);
    uint32_t load_code;

    /*
     * If not going to reset MCP, load "fake" driver to reset HW while
     * driver is owner of the HW.
     */
    if (!global && !BXE_NOMCP(sc)) {
        load_code = bxe_fw_command(sc, DRV_MSG_CODE_LOAD_REQ,
                                   DRV_MSG_CODE_LOAD_REQ_WITH_LFA);
        if (!load_code) {
            BLOGE(sc, "MCP response failure, aborting\n");
            rc = -1;
            goto exit_leader_reset;
        }

        if ((load_code != FW_MSG_CODE_DRV_LOAD_COMMON_CHIP) &&
            (load_code != FW_MSG_CODE_DRV_LOAD_COMMON)) {
            BLOGE(sc, "MCP unexpected response, aborting\n");
            rc = -1;
            goto exit_leader_reset2;
        }

        load_code = bxe_fw_command(sc, DRV_MSG_CODE_LOAD_DONE, 0);
        if (!load_code) {
            BLOGE(sc, "MCP response failure, aborting\n");
            rc = -1;
            goto exit_leader_reset2;
        }
    }

    /* try to recover after the failure */
    if (bxe_process_kill(sc, global)) {
        BLOGE(sc, "Something bad occurred on engine %d!\n", SC_PATH(sc));
        rc = -1;
        goto exit_leader_reset2;
    }

    /*
     * Clear the RESET_IN_PROGRESS and RESET_GLOBAL bits and update the driver
     * state.
     */
    bxe_set_reset_done(sc);
    if (global) {
        bxe_clear_reset_global(sc);
    }

exit_leader_reset2:

    /* unload "fake driver" if it was loaded */
    if (!global && !BXE_NOMCP(sc)) {
        bxe_fw_command(sc, DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP, 0);
        bxe_fw_command(sc, DRV_MSG_CODE_UNLOAD_DONE, 0);
    }

exit_leader_reset:

    sc->is_leader = 0;
    bxe_release_leader_lock(sc);

    mb();
    return (rc);
}