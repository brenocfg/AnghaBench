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
typedef  int /*<<< orphan*/  uint8_t ;
struct dmae_cmd {int /*<<< orphan*/  comp_val; int /*<<< orphan*/  comp_addr_hi; int /*<<< orphan*/  comp_addr_lo; int /*<<< orphan*/  opcode; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_SP_MAPPING (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAE_COMP_PCI ; 
 int /*<<< orphan*/  DMAE_COMP_VAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_dmae_opcode (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dmae_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_comp ; 

__attribute__((used)) static void
bxe_prep_dmae_with_comp(struct bxe_softc    *sc,
                        struct dmae_cmd *dmae,
                        uint8_t             src_type,
                        uint8_t             dst_type)
{
    memset(dmae, 0, sizeof(struct dmae_cmd));

    /* set the opcode */
    dmae->opcode = bxe_dmae_opcode(sc, src_type, dst_type,
                                   TRUE, DMAE_COMP_PCI);

    /* fill in the completion parameters */
    dmae->comp_addr_lo = U64_LO(BXE_SP_MAPPING(sc, wb_comp));
    dmae->comp_addr_hi = U64_HI(BXE_SP_MAPPING(sc, wb_comp));
    dmae->comp_val     = DMAE_COMP_VAL;
}