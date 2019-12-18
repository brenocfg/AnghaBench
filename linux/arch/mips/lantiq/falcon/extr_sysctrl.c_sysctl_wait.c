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
struct clk {unsigned int bits; int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 unsigned int sysctl_r32 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void sysctl_wait(struct clk *clk,
		unsigned int test, unsigned int reg)
{
	int err = 1000000;

	do {} while (--err && ((sysctl_r32(clk->module, reg)
					& clk->bits) != test));
	if (!err)
		pr_err("module de/activation failed %d %08X %08X %08X\n",
			clk->module, clk->bits, test,
			sysctl_r32(clk->module, reg) & clk->bits);
}