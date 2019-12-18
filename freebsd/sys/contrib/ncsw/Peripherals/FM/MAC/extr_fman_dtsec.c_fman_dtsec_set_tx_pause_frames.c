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
typedef  int uint16_t ;
struct dtsec_regs {int /*<<< orphan*/  maccfg1; int /*<<< orphan*/  ptv; } ;

/* Variables and functions */
 int MACCFG1_TX_FLOW ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_dtsec_set_tx_pause_frames(struct dtsec_regs *regs, uint16_t time)
{
	uint32_t ptv = 0;

	/* fixme: don't enable tx pause for half-duplex */

	if (time) {
		ptv = ioread32be(&regs->ptv);
		ptv &= 0xffff0000;
		ptv |= time & 0x0000ffff;
		iowrite32be(ptv, &regs->ptv);

		/* trigger the transmission of a flow-control pause frame */
		iowrite32be(ioread32be(&regs->maccfg1) | MACCFG1_TX_FLOW,
				&regs->maccfg1);
	} else
		iowrite32be(ioread32be(&regs->maccfg1) & ~MACCFG1_TX_FLOW,
				&regs->maccfg1);
}