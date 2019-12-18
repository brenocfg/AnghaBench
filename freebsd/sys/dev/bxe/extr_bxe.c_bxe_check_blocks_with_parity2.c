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
#define  AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR 135 
#define  AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR 134 
#define  AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR 133 
#define  AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR 132 
#define  AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR 131 
#define  AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR 130 
#define  AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR 129 
#define  AEU_IN_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR 128 
 int /*<<< orphan*/  bxe_print_next_block (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bxe_check_blocks_with_parity2(struct bxe_softc *sc,
                              uint32_t         sig,
                              int              par_num,
                              uint8_t          print)
{
    uint32_t cur_bit = 0;
    int i = 0;

    for (i = 0; sig; i++) {
        cur_bit = ((uint32_t)0x1 << i);
        if (sig & cur_bit) {
            switch (cur_bit) {
            case AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "CSEMI");
                break;
            case AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "PXP");
                break;
            case AEU_IN_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "PXPPCICLOCKCLIENT");
                break;
            case AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "CFC");
                break;
            case AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "CDU");
                break;
            case AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "DMAE");
                break;
            case AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "IGU");
                break;
            case AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "MISC");
                break;
            }

            /* Clear the bit */
            sig &= ~cur_bit;
        }
    }

    return (par_num);
}