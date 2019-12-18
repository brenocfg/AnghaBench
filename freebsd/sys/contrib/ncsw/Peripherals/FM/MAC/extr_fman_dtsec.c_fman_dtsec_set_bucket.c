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
struct dtsec_regs {int* gaddr; int* igaddr; } ;

/* Variables and functions */
 int ioread32be (int*) ; 
 int /*<<< orphan*/  iowrite32be (int,int*) ; 

void fman_dtsec_set_bucket(struct dtsec_regs *regs, int bucket, bool enable)
{
	int reg_idx = (bucket >> 5) & 0xf;
	int bit_idx = bucket & 0x1f;
	uint32_t bit_mask = 0x80000000 >> bit_idx;
	uint32_t *reg;

	if (reg_idx > 7)
		reg = &regs->gaddr[reg_idx-8];
	else
		reg = &regs->igaddr[reg_idx];

	if (enable)
		iowrite32be(ioread32be(reg) | bit_mask, reg);
	else
		iowrite32be(ioread32be(reg) & (~bit_mask), reg);
}