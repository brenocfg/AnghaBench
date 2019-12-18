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
typedef  int uint8_t ;
struct dtsec_regs {int /*<<< orphan*/  tbipa; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_dtsec_set_tbi_phy_addr(struct dtsec_regs *regs,
		uint8_t addr)
{
	if (addr > 0 && addr < 32)
		iowrite32be(addr, &regs->tbipa);
	else
		return -EINVAL;

	return 0;
}