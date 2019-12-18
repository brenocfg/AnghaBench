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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_1_CLEAR ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_2_MSTAT0 ; 
 int MISC_REGISTERS_RESET_REG_2_MSTAT1 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static void
bxe_reset_common(struct bxe_softc *sc)
{
    uint32_t val = 0x1400;

    /* reset_common */
    REG_WR(sc, (GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR), 0xd3ffff7f);

    if (CHIP_IS_E3(sc)) {
        val |= MISC_REGISTERS_RESET_REG_2_MSTAT0;
        val |= MISC_REGISTERS_RESET_REG_2_MSTAT1;
    }

    REG_WR(sc, (GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR), val);
}