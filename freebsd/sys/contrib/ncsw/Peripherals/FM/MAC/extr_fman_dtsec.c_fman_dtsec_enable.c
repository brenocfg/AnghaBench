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
struct dtsec_regs {int /*<<< orphan*/  maccfg1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACCFG1_RX_EN ; 
 int /*<<< orphan*/  MACCFG1_TX_EN ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_dtsec_enable(struct dtsec_regs *regs, bool apply_rx, bool apply_tx)
{
	uint32_t tmp;

	tmp = ioread32be(&regs->maccfg1);

	if (apply_rx)
		tmp |= MACCFG1_RX_EN ;

	if (apply_tx)
		tmp |= MACCFG1_TX_EN ;

	iowrite32be(tmp, &regs->maccfg1);
}