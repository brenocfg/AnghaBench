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
struct clk_hw {int dummy; } ;
struct clk_cdce925_output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdce925_clk_set_pdiv (struct clk_cdce925_output*,int /*<<< orphan*/ ) ; 
 struct clk_cdce925_output* to_clk_cdce925_output (struct clk_hw*) ; 

__attribute__((used)) static void cdce925_clk_unprepare(struct clk_hw *hw)
{
	struct clk_cdce925_output *data = to_clk_cdce925_output(hw);

	/* Disable clock by setting divider to "0" */
	cdce925_clk_set_pdiv(data, 0);
}