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
struct bxe_softc {int /*<<< orphan*/  pcie_device; int /*<<< orphan*/  pcie_bus; } ;
struct bxe_prev_list_node {int undi; scalar_t__ aer; int /*<<< orphan*/  path; int /*<<< orphan*/  slot; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bxe_prev_list_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SC_PATH (struct bxe_softc*) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_prev_list ; 
 int /*<<< orphan*/  bxe_prev_mtx ; 
 struct bxe_prev_list_node* bxe_prev_path_get_entry (struct bxe_softc*) ; 
 struct bxe_prev_list_node* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node ; 

__attribute__((used)) static int
bxe_prev_mark_path(struct bxe_softc *sc,
                   uint8_t          after_undi)
{
    struct bxe_prev_list_node *tmp;

    mtx_lock(&bxe_prev_mtx);

    /* Check whether the entry for this path already exists */
    tmp = bxe_prev_path_get_entry(sc);
    if (tmp) {
        if (!tmp->aer) {
            BLOGD(sc, DBG_LOAD,
                  "Re-marking AER in path %d/%d/%d\n",
                  sc->pcie_bus, sc->pcie_device, SC_PATH(sc));
        } else {
            BLOGD(sc, DBG_LOAD,
                  "Removing AER indication from path %d/%d/%d\n",
                  sc->pcie_bus, sc->pcie_device, SC_PATH(sc));
            tmp->aer = 0;
        }

        mtx_unlock(&bxe_prev_mtx);
        return (0);
    }

    mtx_unlock(&bxe_prev_mtx);

    /* Create an entry for this path and add it */
    tmp = malloc(sizeof(struct bxe_prev_list_node), M_DEVBUF,
                 (M_NOWAIT | M_ZERO));
    if (!tmp) {
        BLOGE(sc, "Failed to allocate 'bxe_prev_list_node'\n");
        return (-1);
    }

    tmp->bus  = sc->pcie_bus;
    tmp->slot = sc->pcie_device;
    tmp->path = SC_PATH(sc);
    tmp->aer  = 0;
    tmp->undi = after_undi ? (1 << SC_PORT(sc)) : 0;

    mtx_lock(&bxe_prev_mtx);

    BLOGD(sc, DBG_LOAD,
          "Marked path %d/%d/%d - finished previous unload\n",
          sc->pcie_bus, sc->pcie_device, SC_PATH(sc));
    LIST_INSERT_HEAD(&bxe_prev_list, tmp, node);

    mtx_unlock(&bxe_prev_mtx);

    return (0);
}