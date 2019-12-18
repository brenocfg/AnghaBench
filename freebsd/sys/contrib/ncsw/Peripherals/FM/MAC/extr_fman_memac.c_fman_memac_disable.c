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
typedef  int /*<<< orphan*/  uint32_t ;
struct memac_regs {int /*<<< orphan*/  command_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CFG_RX_EN ; 
 int /*<<< orphan*/  CMD_CFG_TX_EN ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_memac_disable(struct memac_regs *regs, bool apply_rx, bool apply_tx)
{
    uint32_t tmp;

    tmp = ioread32be(&regs->command_config);

    if (apply_rx)
        tmp &= ~CMD_CFG_RX_EN;

    if (apply_tx)
        tmp &= ~CMD_CFG_TX_EN;

    iowrite32be(tmp, &regs->command_config);
}