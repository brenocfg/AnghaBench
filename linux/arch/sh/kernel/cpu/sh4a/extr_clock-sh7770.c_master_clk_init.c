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
struct clk {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCR ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pfc_divisors ; 

__attribute__((used)) static void master_clk_init(struct clk *clk)
{
	clk->rate *= pfc_divisors[(__raw_readl(FRQCR) >> 28) & 0x000f];
}