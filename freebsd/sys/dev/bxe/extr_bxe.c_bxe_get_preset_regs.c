#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct wreg_addr {size_t size; size_t addr; size_t read_regs_count; size_t* read_regs; int /*<<< orphan*/  presets; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_4__ {size_t size; size_t addr; int /*<<< orphan*/  presets; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3A0 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3B0 (struct bxe_softc*) ; 
 size_t IDLE_REGS_COUNT ; 
 scalar_t__ IS_REG_IN_PRESET (int /*<<< orphan*/ ,size_t) ; 
 size_t REGS_COUNT ; 
 void* REG_RD (struct bxe_softc*,size_t) ; 
 scalar_t__ bxe_is_reg_in_chip (struct bxe_softc*,TYPE_1__*) ; 
 scalar_t__ bxe_is_wreg_in_chip (struct bxe_softc*,struct wreg_addr const*) ; 
 int /*<<< orphan*/  bxe_read_pages_regs (struct bxe_softc*,size_t*,size_t) ; 
 TYPE_1__* idle_reg_addrs ; 
 TYPE_1__* reg_addrs ; 
 struct wreg_addr wreg_addr_e1 ; 
 struct wreg_addr wreg_addr_e1h ; 
 struct wreg_addr wreg_addr_e2 ; 
 struct wreg_addr wreg_addr_e3 ; 
 struct wreg_addr wreg_addr_e3b0 ; 

__attribute__((used)) static int
bxe_get_preset_regs(struct bxe_softc *sc, uint32_t *p, uint32_t preset)
{
    uint32_t i, j, addr;
    const struct wreg_addr *wreg_addr_p = NULL;

    if (CHIP_IS_E1(sc))
        wreg_addr_p = &wreg_addr_e1;
    else if (CHIP_IS_E1H(sc))
        wreg_addr_p = &wreg_addr_e1h;
    else if (CHIP_IS_E2(sc))
        wreg_addr_p = &wreg_addr_e2;
    else if (CHIP_IS_E3A0(sc))
        wreg_addr_p = &wreg_addr_e3;
    else if (CHIP_IS_E3B0(sc))
        wreg_addr_p = &wreg_addr_e3b0;
    else
        return (-1);

    /* Read the idle_chk registers */
    for (i = 0; i < IDLE_REGS_COUNT; i++) {
        if (bxe_is_reg_in_chip(sc, &idle_reg_addrs[i]) &&
            IS_REG_IN_PRESET(idle_reg_addrs[i].presets, preset)) {
            for (j = 0; j < idle_reg_addrs[i].size; j++)
                *p++ = REG_RD(sc, idle_reg_addrs[i].addr + j*4);
        }
    }

    /* Read the regular registers */
    for (i = 0; i < REGS_COUNT; i++) {
        if (bxe_is_reg_in_chip(sc, &reg_addrs[i]) &&
            IS_REG_IN_PRESET(reg_addrs[i].presets, preset)) {
            for (j = 0; j < reg_addrs[i].size; j++)
                *p++ = REG_RD(sc, reg_addrs[i].addr + j*4);
        }
    }

    /* Read the CAM registers */
    if (bxe_is_wreg_in_chip(sc, wreg_addr_p) &&
        IS_REG_IN_PRESET(wreg_addr_p->presets, preset)) {
        for (i = 0; i < wreg_addr_p->size; i++) {
            *p++ = REG_RD(sc, wreg_addr_p->addr + i*4);

            /* In case of wreg_addr register, read additional
               registers from read_regs array
             */
            for (j = 0; j < wreg_addr_p->read_regs_count; j++) {
                addr = *(wreg_addr_p->read_regs);
                *p++ = REG_RD(sc, addr + j*4);
            }
        }
    }

    /* Paged registers are supported in E2 & E3 only */
    if (CHIP_IS_E2(sc) || CHIP_IS_E3(sc)) {
        /* Read "paged" registers */
        bxe_read_pages_regs(sc, p, preset);
    }

    return 0;
}