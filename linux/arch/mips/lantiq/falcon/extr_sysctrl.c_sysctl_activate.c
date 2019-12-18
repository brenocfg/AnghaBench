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
struct clk {int /*<<< orphan*/  bits; int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSCTL_ACT ; 
 int /*<<< orphan*/  SYSCTL_ACTS ; 
 int /*<<< orphan*/  SYSCTL_CLKEN ; 
 int /*<<< orphan*/  sysctl_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_wait (struct clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysctl_activate(struct clk *clk)
{
	sysctl_w32(clk->module, clk->bits, SYSCTL_CLKEN);
	sysctl_w32(clk->module, clk->bits, SYSCTL_ACT);
	sysctl_wait(clk, clk->bits, SYSCTL_ACTS);
	return 0;
}