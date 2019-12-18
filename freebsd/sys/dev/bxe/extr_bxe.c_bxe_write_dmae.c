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
typedef  int uint32_t ;
struct dmae_cmd {int dst_addr_lo; int len; scalar_t__ dst_addr_hi; int /*<<< orphan*/  src_addr_hi; int /*<<< orphan*/  src_addr_lo; } ;
struct bxe_softc {int /*<<< orphan*/  dmae_ready; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBASSERT (struct bxe_softc*,int,char*) ; 
 int /*<<< orphan*/  DMAE_DST_GRC ; 
 int /*<<< orphan*/  DMAE_SRC_PCI ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bxe_issue_dmae_with_comp (struct bxe_softc*,struct dmae_cmd*) ; 
 int /*<<< orphan*/  bxe_panic (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  bxe_prep_dmae_with_comp (struct bxe_softc*,struct dmae_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_ind_wr (struct bxe_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_init_str_wr (struct bxe_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * wb_data ; 

void
bxe_write_dmae(struct bxe_softc *sc,
               bus_addr_t       dma_addr,
               uint32_t         dst_addr,
               uint32_t         len32)
{
    struct dmae_cmd dmae;
    int rc;

    if (!sc->dmae_ready) {
        DBASSERT(sc, (len32 <= 4), ("DMAE not ready and length is %d", len32));

        if (CHIP_IS_E1(sc)) {
            ecore_init_ind_wr(sc, dst_addr, BXE_SP(sc, wb_data[0]), len32);
        } else {
            ecore_init_str_wr(sc, dst_addr, BXE_SP(sc, wb_data[0]), len32);
        }

        return;
    }

    /* set opcode and fixed command fields */
    bxe_prep_dmae_with_comp(sc, &dmae, DMAE_SRC_PCI, DMAE_DST_GRC);

    /* fill in addresses and len */
    dmae.src_addr_lo = U64_LO(dma_addr);
    dmae.src_addr_hi = U64_HI(dma_addr);
    dmae.dst_addr_lo = (dst_addr >> 2); /* GRC addr has dword resolution */
    dmae.dst_addr_hi = 0;
    dmae.len         = len32;

    /* issue the command and wait for completion */
    if ((rc = bxe_issue_dmae_with_comp(sc, &dmae)) != 0) {
        bxe_panic(sc, ("DMAE failed (%d)\n", rc));
    }
}