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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int DMAE_CMD_DST_RESET ; 
 int DMAE_CMD_DST_SHIFT ; 
 int DMAE_CMD_DST_VN_SHIFT ; 
 int DMAE_CMD_E1HVN_SHIFT ; 
 int DMAE_CMD_ENDIANITY_B_DW_SWAP ; 
 int DMAE_CMD_ENDIANITY_DW_SWAP ; 
 int DMAE_CMD_ERR_POLICY_SHIFT ; 
 int DMAE_CMD_PORT_0 ; 
 int DMAE_CMD_PORT_1 ; 
 int DMAE_CMD_SRC_RESET ; 
 int DMAE_CMD_SRC_SHIFT ; 
 int DMAE_COM_SET_ERR ; 
 scalar_t__ SC_PORT (struct bxe_softc*) ; 
 int SC_VN (struct bxe_softc*) ; 
 int bxe_dmae_opcode_add_comp (int,int) ; 

uint32_t
bxe_dmae_opcode(struct bxe_softc *sc,
                uint8_t          src_type,
                uint8_t          dst_type,
                uint8_t          with_comp,
                uint8_t          comp_type)
{
    uint32_t opcode = 0;

    opcode |= ((src_type << DMAE_CMD_SRC_SHIFT) |
               (dst_type << DMAE_CMD_DST_SHIFT));

    opcode |= (DMAE_CMD_SRC_RESET | DMAE_CMD_DST_RESET);

    opcode |= (SC_PORT(sc) ? DMAE_CMD_PORT_1 : DMAE_CMD_PORT_0);

    opcode |= ((SC_VN(sc) << DMAE_CMD_E1HVN_SHIFT) |
               (SC_VN(sc) << DMAE_CMD_DST_VN_SHIFT));

    opcode |= (DMAE_COM_SET_ERR << DMAE_CMD_ERR_POLICY_SHIFT);

#ifdef __BIG_ENDIAN
    opcode |= DMAE_CMD_ENDIANITY_B_DW_SWAP;
#else
    opcode |= DMAE_CMD_ENDIANITY_DW_SWAP;
#endif

    if (with_comp) {
        opcode = bxe_dmae_opcode_add_comp(opcode, comp_type);
    }

    return (opcode);
}