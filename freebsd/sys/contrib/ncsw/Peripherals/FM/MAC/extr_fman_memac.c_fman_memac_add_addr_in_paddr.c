#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr_u; int /*<<< orphan*/  mac_addr_l; } ;
struct memac_regs {TYPE_2__* mac_addr; TYPE_1__ mac_addr0; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac_addr_u; int /*<<< orphan*/  mac_addr_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (scalar_t__,int /*<<< orphan*/ *) ; 

void fman_memac_add_addr_in_paddr(struct memac_regs *regs,
                    uint8_t *adr,
                    uint8_t paddr_num)
{
    uint32_t tmp0, tmp1;

    tmp0 = (uint32_t)(adr[0] |
            adr[1] << 8 |
            adr[2] << 16 |
            adr[3] << 24);
    tmp1 = (uint32_t)(adr[4] | adr[5] << 8);

    if (paddr_num == 0) {
        iowrite32be(tmp0, &regs->mac_addr0.mac_addr_l);
        iowrite32be(tmp1, &regs->mac_addr0.mac_addr_u);
    } else {
        iowrite32be(tmp0, &regs->mac_addr[paddr_num-1].mac_addr_l);
        iowrite32be(tmp1, &regs->mac_addr[paddr_num-1].mac_addr_u);
    }
}