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
struct tgec_regs {int /*<<< orphan*/  tx_ipg_len; } ;

/* Variables and functions */
 int TGEC_TX_IPG_LENGTH_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_tgec_set_erratum_tx_fifo_corruption_10gmac_a007(struct tgec_regs *regs)
{
	uint32_t tmp;

	/* restore the default tx ipg Length */
	tmp = (ioread32be(&regs->tx_ipg_len) & ~TGEC_TX_IPG_LENGTH_MASK) | 12;

	iowrite32be(tmp, &regs->tx_ipg_len);
}