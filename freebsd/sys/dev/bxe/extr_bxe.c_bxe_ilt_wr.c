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
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int ONCHIP_ADDR1 (int /*<<< orphan*/ ) ; 
 int ONCHIP_ADDR2 (int /*<<< orphan*/ ) ; 
 int PXP2_REG_RQ_ONCHIP_AT ; 
 int PXP2_REG_RQ_ONCHIP_AT_B0 ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bxe_softc*,int,int*,int) ; 

__attribute__((used)) static void
bxe_ilt_wr(struct bxe_softc *sc,
           uint32_t         index,
           bus_addr_t       addr)
{
    int reg;
    uint32_t wb_write[2];

    if (CHIP_IS_E1(sc)) {
        reg = PXP2_REG_RQ_ONCHIP_AT + index*8;
    } else {
        reg = PXP2_REG_RQ_ONCHIP_AT_B0 + index*8;
    }

    wb_write[0] = ONCHIP_ADDR1(addr);
    wb_write[1] = ONCHIP_ADDR2(addr);
    REG_WR_DMAE(sc, reg, wb_write, 2);
}