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
#define  AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR 143 
#define  AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR 142 
#define  AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR 141 
#define  AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR 140 
#define  AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR 139 
#define  AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR 138 
#define  AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR 137 
#define  AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR 136 
#define  AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR 135 
#define  AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR 134 
#define  AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR 133 
#define  AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR 132 
#define  AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR 131 
#define  AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR 130 
#define  AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR 129 
#define  AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bxe_print_next_block (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bxe_check_blocks_with_parity1(struct bxe_softc *sc,
                              uint32_t         sig,
                              int              par_num,
                              uint8_t          *global,
                              uint8_t          print)
{
    int i = 0;
    uint32_t cur_bit = 0;
    for (i = 0; sig; i++) {
        cur_bit = ((uint32_t)0x1 << i);
        if (sig & cur_bit) {
            switch (cur_bit) {
            case AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "PBF");
                break;
            case AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "QM");
                break;
            case AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "TM");
                break;
            case AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "XSDM");
                break;
            case AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "XCM");
                break;
            case AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "XSEMI");
                break;
            case AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "DOORBELLQ");
                break;
            case AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "NIG");
                break;
            case AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "VAUX PCI CORE");
                *global = TRUE;
                break;
            case AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "DEBUG");
                break;
            case AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "USDM");
                break;
            case AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "UCM");
                break;
            case AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "USEMI");
                break;
            case AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "UPB");
                break;
            case AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "CSDM");
                break;
            case AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR:
                if (print)
                    bxe_print_next_block(sc, par_num++, "CCM");
                break;
            }

            /* Clear the bit */
            sig &= ~cur_bit;
        }
    }

    return (par_num);
}