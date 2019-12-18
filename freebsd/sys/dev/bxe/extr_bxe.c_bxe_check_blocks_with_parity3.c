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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY 131 
#define  AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY 130 
#define  AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY 129 
#define  AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bxe_print_next_block (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bxe_check_blocks_with_parity3(struct bxe_softc *sc,
                              uint32_t         sig,
                              int              par_num,
                              uint8_t          *global,
                              uint8_t          print)
{
    uint32_t cur_bit = 0;
    int i = 0;

    for (i = 0; sig; i++) {
        cur_bit = ((uint32_t)0x1 << i);
        if (sig & cur_bit) {
            switch (cur_bit) {
            case AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY:
                if (print)
                    bxe_print_next_block(sc, par_num++, "MCP ROM");
                *global = TRUE;
                break;
            case AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY:
                if (print)
                    bxe_print_next_block(sc, par_num++,
                              "MCP UMP RX");
                *global = TRUE;
                break;
            case AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY:
                if (print)
                    bxe_print_next_block(sc, par_num++,
                              "MCP UMP TX");
                *global = TRUE;
                break;
            case AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY:
                if (print)
                    bxe_print_next_block(sc, par_num++,
                              "MCP SCPAD");
                *global = TRUE;
                break;
            }

            /* Clear the bit */
            sig &= ~cur_bit;
        }
    }

    return (par_num);
}