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
struct mmp_clk_unit {int dummy; } ;
struct pxa168_clk_unit {int /*<<< orphan*/  apbc_base; struct mmp_clk_unit unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apbc_gate_clks ; 
 int /*<<< orphan*/  apbc_mux_clks ; 
 int /*<<< orphan*/  mmp_register_gate_clks (struct mmp_clk_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_register_mux_clks (struct mmp_clk_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa168_apb_periph_clk_init(struct pxa168_clk_unit *pxa_unit)
{
	struct mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_register_mux_clks(unit, apbc_mux_clks, pxa_unit->apbc_base,
				ARRAY_SIZE(apbc_mux_clks));

	mmp_register_gate_clks(unit, apbc_gate_clks, pxa_unit->apbc_base,
				ARRAY_SIZE(apbc_gate_clks));

}