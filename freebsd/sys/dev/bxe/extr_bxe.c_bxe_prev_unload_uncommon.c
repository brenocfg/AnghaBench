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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int BXE_PREV_WAIT_NEEDED ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  FW_MSG_CODE_DRV_LOAD_FUNCTION ; 
 int bxe_do_flr (struct bxe_softc*) ; 
 int bxe_nic_load_analyze_req (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bxe_prev_is_path_marked (struct bxe_softc*) ; 
 int bxe_prev_mcp_done (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_prev_unload_uncommon(struct bxe_softc *sc)
{
    int rc;

    BLOGD(sc, DBG_LOAD, "Uncommon unload Flow\n");

    /* Test if previous unload process was already finished for this path */
    if (bxe_prev_is_path_marked(sc)) {
        return (bxe_prev_mcp_done(sc));
    }

    BLOGD(sc, DBG_LOAD, "Path is unmarked\n");

    /*
     * If function has FLR capabilities, and existing FW version matches
     * the one required, then FLR will be sufficient to clean any residue
     * left by previous driver
     */
    rc = bxe_nic_load_analyze_req(sc, FW_MSG_CODE_DRV_LOAD_FUNCTION);
    if (!rc) {
        /* fw version is good */
        BLOGD(sc, DBG_LOAD, "FW version matches our own, attempting FLR\n");
        rc = bxe_do_flr(sc);
    }

    if (!rc) {
        /* FLR was performed */
        BLOGD(sc, DBG_LOAD, "FLR successful\n");
        return (0);
    }

    BLOGD(sc, DBG_LOAD, "Could not FLR\n");

    /* Close the MCP request, return failure*/
    rc = bxe_prev_mcp_done(sc);
    if (!rc) {
        rc = BXE_PREV_WAIT_NEEDED;
    }

    return (rc);
}