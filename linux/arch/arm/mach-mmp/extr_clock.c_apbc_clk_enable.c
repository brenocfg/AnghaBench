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
struct clk {int /*<<< orphan*/  clk_rst; int /*<<< orphan*/  fnclksel; } ;

/* Variables and functions */
 int APBC_APBCLK ; 
 int APBC_FNCLK ; 
 int APBC_FNCLKSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apbc_clk_enable(struct clk *clk)
{
	uint32_t clk_rst;

	clk_rst = APBC_APBCLK | APBC_FNCLK | APBC_FNCLKSEL(clk->fnclksel);
	__raw_writel(clk_rst, clk->clk_rst);
}