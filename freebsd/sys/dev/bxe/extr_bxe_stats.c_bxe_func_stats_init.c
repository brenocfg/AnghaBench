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
typedef  scalar_t__ uint32_t ;
struct host_func_stats {int dummy; } ;
struct dmae_cmd {int dst_addr_lo; int len; int /*<<< orphan*/  comp_val; void* comp_addr_hi; void* comp_addr_lo; scalar_t__ dst_addr_hi; void* src_addr_hi; void* src_addr_lo; int /*<<< orphan*/  opcode; } ;
struct bxe_softc {int func_stx; scalar_t__ executer_idx; struct dmae_cmd stats_dmae; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 scalar_t__* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_SP_MAPPING (struct bxe_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  DMAE_COMP_PCI ; 
 int /*<<< orphan*/  DMAE_COMP_VAL ; 
 int /*<<< orphan*/  DMAE_DST_GRC ; 
 int /*<<< orphan*/  DMAE_SRC_PCI ; 
 int /*<<< orphan*/  TRUE ; 
 void* U64_HI (int /*<<< orphan*/ ) ; 
 void* U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_dmae_opcode (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* func_stats ; 
 int /*<<< orphan*/  memset (struct dmae_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* stats_comp ; 

__attribute__((used)) static void
bxe_func_stats_init(struct bxe_softc *sc)
{
    struct dmae_cmd *dmae = &sc->stats_dmae;
    uint32_t *stats_comp = BXE_SP(sc, stats_comp);

    /* sanity */
    if (!sc->func_stx) {
        BLOGE(sc, "BUG!\n");
        return;
    }

    sc->executer_idx = 0;
    memset(dmae, 0, sizeof(struct dmae_cmd));

    dmae->opcode = bxe_dmae_opcode(sc, DMAE_SRC_PCI, DMAE_DST_GRC,
                                   TRUE, DMAE_COMP_PCI);
    dmae->src_addr_lo = U64_LO(BXE_SP_MAPPING(sc, func_stats));
    dmae->src_addr_hi = U64_HI(BXE_SP_MAPPING(sc, func_stats));
    dmae->dst_addr_lo = (sc->func_stx >> 2);
    dmae->dst_addr_hi = 0;
    dmae->len = (sizeof(struct host_func_stats) >> 2);
    dmae->comp_addr_lo = U64_LO(BXE_SP_MAPPING(sc, stats_comp));
    dmae->comp_addr_hi = U64_HI(BXE_SP_MAPPING(sc, stats_comp));
    dmae->comp_val = DMAE_COMP_VAL;

    *stats_comp = 0;
}