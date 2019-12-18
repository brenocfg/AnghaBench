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
struct dtsec_regs {int /*<<< orphan*/  maccfg2; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACCFG2_MAGIC_PACKET_EN ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_dtsec_set_wol(struct dtsec_regs *regs, bool en)
{
	uint32_t tmp;

	tmp = ioread32be(&regs->maccfg2);
	if (en)
		tmp |= MACCFG2_MAGIC_PACKET_EN;
	else
		tmp &= ~MACCFG2_MAGIC_PACKET_EN;
	iowrite32be(tmp, &regs->maccfg2);
}