#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  shmem2_base; int /*<<< orphan*/  shmem_base; int /*<<< orphan*/  chip_id; } ;
struct bxe_softc {int num_queues; TYPE_1__ devinfo; int /*<<< orphan*/  link_vars; } ;

/* Variables and functions */
 int AEU_INPUTS_ATTN_BITS_SPIO5 ; 
 scalar_t__ IS_VF (struct bxe_softc*) ; 
 scalar_t__ MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_attn_int_deasserted0 (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_init_def_sb (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_init_eq_ring (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_init_eth_fp (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_init_internal (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_init_rx_rings (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_init_sp_ring (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_init_tx_rings (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_int_enable (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_pf_init (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_init (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_update_dsb_idx (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_init_mod_abs_int (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void
bxe_nic_init(struct bxe_softc *sc,
             int              load_code)
{
    int i;

    for (i = 0; i < sc->num_queues; i++) {
        bxe_init_eth_fp(sc, i);
    }

    rmb(); /* ensure status block indices were read */

    bxe_init_rx_rings(sc);
    bxe_init_tx_rings(sc);

    if (IS_VF(sc)) {
        return;
    }

    /* initialize MOD_ABS interrupts */
    elink_init_mod_abs_int(sc, &sc->link_vars,
                           sc->devinfo.chip_id,
                           sc->devinfo.shmem_base,
                           sc->devinfo.shmem2_base,
                           SC_PORT(sc));

    bxe_init_def_sb(sc);
    bxe_update_dsb_idx(sc);
    bxe_init_sp_ring(sc);
    bxe_init_eq_ring(sc);
    bxe_init_internal(sc, load_code);
    bxe_pf_init(sc);
    bxe_stats_init(sc);

    /* flush all before enabling interrupts */
    mb();

    bxe_int_enable(sc);

    /* check for SPIO5 */
    bxe_attn_int_deasserted0(sc,
                             REG_RD(sc,
                                    (MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 +
                                     SC_PORT(sc)*4)) &
                             AEU_INPUTS_ATTN_BITS_SPIO5);
}