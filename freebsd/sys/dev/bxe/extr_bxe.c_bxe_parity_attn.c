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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_ERR_GLOBAL ; 
 int /*<<< orphan*/  BXE_SET_ERROR_BIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int HW_PRTY_ASSERT_SET_0 ; 
 int HW_PRTY_ASSERT_SET_1 ; 
 int HW_PRTY_ASSERT_SET_2 ; 
 int HW_PRTY_ASSERT_SET_3 ; 
 int HW_PRTY_ASSERT_SET_4 ; 
 scalar_t__ TRUE ; 
 int bxe_check_blocks_with_parity0 (struct bxe_softc*,int,int,scalar_t__) ; 
 int bxe_check_blocks_with_parity1 (struct bxe_softc*,int,int,scalar_t__*,scalar_t__) ; 
 int bxe_check_blocks_with_parity2 (struct bxe_softc*,int,int,scalar_t__) ; 
 int bxe_check_blocks_with_parity3 (struct bxe_softc*,int,int,scalar_t__*,scalar_t__) ; 
 int bxe_check_blocks_with_parity4 (struct bxe_softc*,int,int,scalar_t__) ; 

__attribute__((used)) static uint8_t
bxe_parity_attn(struct bxe_softc *sc,
                uint8_t          *global,
                uint8_t          print,
                uint32_t         *sig)
{
    int par_num = 0;

    if ((sig[0] & HW_PRTY_ASSERT_SET_0) ||
        (sig[1] & HW_PRTY_ASSERT_SET_1) ||
        (sig[2] & HW_PRTY_ASSERT_SET_2) ||
        (sig[3] & HW_PRTY_ASSERT_SET_3) ||
        (sig[4] & HW_PRTY_ASSERT_SET_4)) {
        BLOGE(sc, "Parity error: HW block parity attention:\n"
                  "[0]:0x%08x [1]:0x%08x [2]:0x%08x [3]:0x%08x [4]:0x%08x\n",
              (uint32_t)(sig[0] & HW_PRTY_ASSERT_SET_0),
              (uint32_t)(sig[1] & HW_PRTY_ASSERT_SET_1),
              (uint32_t)(sig[2] & HW_PRTY_ASSERT_SET_2),
              (uint32_t)(sig[3] & HW_PRTY_ASSERT_SET_3),
              (uint32_t)(sig[4] & HW_PRTY_ASSERT_SET_4));

        if (print)
            BLOGI(sc, "Parity errors detected in blocks: ");

        par_num =
            bxe_check_blocks_with_parity0(sc, sig[0] &
                                          HW_PRTY_ASSERT_SET_0,
                                          par_num, print);
        par_num =
            bxe_check_blocks_with_parity1(sc, sig[1] &
                                          HW_PRTY_ASSERT_SET_1,
                                          par_num, global, print);
        par_num =
            bxe_check_blocks_with_parity2(sc, sig[2] &
                                          HW_PRTY_ASSERT_SET_2,
                                          par_num, print);
        par_num =
            bxe_check_blocks_with_parity3(sc, sig[3] &
                                          HW_PRTY_ASSERT_SET_3,
                                          par_num, global, print);
        par_num =
            bxe_check_blocks_with_parity4(sc, sig[4] &
                                          HW_PRTY_ASSERT_SET_4,
                                          par_num, print);

        if (print)
            BLOGI(sc, "\n");

	if( *global == TRUE ) {
                BXE_SET_ERROR_BIT(sc, BXE_ERR_GLOBAL);
        }

        return (TRUE);
    }

    return (FALSE);
}