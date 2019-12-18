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
typedef  int uint8_t ;
struct bxe_softc {int /*<<< orphan*/  pcie_device; int /*<<< orphan*/  pcie_bus; } ;
struct bxe_prev_list_node {scalar_t__ aer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int FALSE ; 
 int /*<<< orphan*/  SC_PATH (struct bxe_softc*) ; 
 int TRUE ; 
 int /*<<< orphan*/  bxe_prev_mtx ; 
 struct bxe_prev_list_node* bxe_prev_path_get_entry (struct bxe_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint8_t
bxe_prev_is_path_marked(struct bxe_softc *sc)
{
    struct bxe_prev_list_node *tmp;
    int rc = FALSE;

    mtx_lock(&bxe_prev_mtx);

    tmp = bxe_prev_path_get_entry(sc);
    if (tmp) {
        if (tmp->aer) {
            BLOGD(sc, DBG_LOAD,
                  "Path %d/%d/%d was marked by AER\n",
                  sc->pcie_bus, sc->pcie_device, SC_PATH(sc));
        } else {
            rc = TRUE;
            BLOGD(sc, DBG_LOAD,
                  "Path %d/%d/%d was already cleaned from previous drivers\n",
                  sc->pcie_bus, sc->pcie_device, SC_PATH(sc));
        }
    }

    mtx_unlock(&bxe_prev_mtx);

    return (rc);
}