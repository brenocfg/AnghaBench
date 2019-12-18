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
struct dmae_cmd {int src_addr_lo; int len; int /*<<< orphan*/  dst_addr_hi; int /*<<< orphan*/  dst_addr_lo; scalar_t__ src_addr_hi; } ;
struct bxe_softc {int /*<<< orphan*/  dmae_ready; } ;

/* Variables and functions */
 int* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_SP_MAPPING (struct bxe_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBASSERT (struct bxe_softc*,int,char*) ; 
 int /*<<< orphan*/  DMAE_DST_PCI ; 
 int /*<<< orphan*/  DMAE_SRC_GRC ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bxe_issue_dmae_with_comp (struct bxe_softc*,struct dmae_cmd*) ; 
 int /*<<< orphan*/  bxe_panic (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  bxe_prep_dmae_with_comp (struct bxe_softc*,struct dmae_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bxe_reg_rd_ind (struct bxe_softc*,int) ; 
 int /*<<< orphan*/ * wb_data ; 

void
bxe_read_dmae(struct bxe_softc *sc,
              uint32_t         src_addr,
              uint32_t         len32)
{
    struct dmae_cmd dmae;
    uint32_t *data;
    int i, rc;

    DBASSERT(sc, (len32 <= 4), ("DMAE read length is %d", len32));

    if (!sc->dmae_ready) {
        data = BXE_SP(sc, wb_data[0]);

        for (i = 0; i < len32; i++) {
            data[i] = (CHIP_IS_E1(sc)) ?
                          bxe_reg_rd_ind(sc, (src_addr + (i * 4))) :
                          REG_RD(sc, (src_addr + (i * 4)));
        }

        return;
    }

    /* set opcode and fixed command fields */
    bxe_prep_dmae_with_comp(sc, &dmae, DMAE_SRC_GRC, DMAE_DST_PCI);

    /* fill in addresses and len */
    dmae.src_addr_lo = (src_addr >> 2); /* GRC addr has dword resolution */
    dmae.src_addr_hi = 0;
    dmae.dst_addr_lo = U64_LO(BXE_SP_MAPPING(sc, wb_data));
    dmae.dst_addr_hi = U64_HI(BXE_SP_MAPPING(sc, wb_data));
    dmae.len         = len32;

    /* issue the command and wait for completion */
    if ((rc = bxe_issue_dmae_with_comp(sc, &dmae)) != 0) {
        bxe_panic(sc, ("DMAE failed (%d)\n", rc));
    }
}