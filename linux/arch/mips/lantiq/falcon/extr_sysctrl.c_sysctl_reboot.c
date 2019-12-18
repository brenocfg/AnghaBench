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
 int /*<<< orphan*/  SYSCTL_ACT ; 
 int /*<<< orphan*/  SYSCTL_ACTS ; 
 int /*<<< orphan*/  SYSCTL_CLKEN ; 
 int /*<<< orphan*/  SYSCTL_RBT ; 
 unsigned int sysctl_r32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_w32 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_wait (struct clk*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysctl_reboot(struct clk *clk)
{
	unsigned int act;
	unsigned int bits;

	act = sysctl_r32(clk->module, SYSCTL_ACT);
	bits = ~act & clk->bits;
	if (bits != 0) {
		sysctl_w32(clk->module, bits, SYSCTL_CLKEN);
		sysctl_w32(clk->module, bits, SYSCTL_ACT);
		sysctl_wait(clk, bits, SYSCTL_ACTS);
	}
	sysctl_w32(clk->module, act & clk->bits, SYSCTL_RBT);
	sysctl_wait(clk, clk->bits, SYSCTL_ACTS);
}