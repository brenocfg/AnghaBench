#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scpi_clk {int /*<<< orphan*/  id; TYPE_1__* scpi_ops; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long (* clk_get_val ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned long stub1 (int /*<<< orphan*/ ) ; 
 struct scpi_clk* to_scpi_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long scpi_clk_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct scpi_clk *clk = to_scpi_clk(hw);

	return clk->scpi_ops->clk_get_val(clk->id);
}