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
typedef  int uint16_t ;
struct bxe_softc {int mrrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int PCIM_EXP_CTL_MAX_PAYLOAD ; 
 int PCIM_EXP_CTL_MAX_READ_REQUEST ; 
 int /*<<< orphan*/  PCIR_EXPRESS_DEVICE_CTL ; 
 int bxe_pcie_capability_read (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_init_pxp_arb (struct bxe_softc*,int,int) ; 

__attribute__((used)) static void
bxe_init_pxp(struct bxe_softc *sc)
{
    uint16_t devctl;
    int r_order, w_order;

    devctl = bxe_pcie_capability_read(sc, PCIR_EXPRESS_DEVICE_CTL, 2);

    BLOGD(sc, DBG_LOAD, "read 0x%08x from devctl\n", devctl);

    w_order = ((devctl & PCIM_EXP_CTL_MAX_PAYLOAD) >> 5);

    if (sc->mrrs == -1) {
        r_order = ((devctl & PCIM_EXP_CTL_MAX_READ_REQUEST) >> 12);
    } else {
        BLOGD(sc, DBG_LOAD, "forcing read order to %d\n", sc->mrrs);
        r_order = sc->mrrs;
    }

    ecore_init_pxp_arb(sc, r_order, w_order);
}