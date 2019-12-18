#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pxa910_clk_unit {scalar_t__ apbc_base; } ;
struct mmp_clk_reset_cell {int bits; int /*<<< orphan*/  lock; scalar_t__ flags; scalar_t__ reg; int /*<<< orphan*/  clk_id; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ offset; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* apbc_gate_clks ; 
 TYPE_1__* apbcp_gate_clks ; 
 struct mmp_clk_reset_cell* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_clk_reset_register (struct device_node*,struct mmp_clk_reset_cell*,int) ; 

__attribute__((used)) static void pxa910_clk_reset_init(struct device_node *np,
				struct pxa910_clk_unit *pxa_unit)
{
	struct mmp_clk_reset_cell *cells;
	int i, base, nr_resets_apbc, nr_resets_apbcp, nr_resets;

	nr_resets_apbc = ARRAY_SIZE(apbc_gate_clks);
	nr_resets_apbcp = ARRAY_SIZE(apbcp_gate_clks);
	nr_resets = nr_resets_apbc + nr_resets_apbcp;
	cells = kcalloc(nr_resets, sizeof(*cells), GFP_KERNEL);
	if (!cells)
		return;

	base = 0;
	for (i = 0; i < nr_resets_apbc; i++) {
		cells[base + i].clk_id = apbc_gate_clks[i].id;
		cells[base + i].reg =
			pxa_unit->apbc_base + apbc_gate_clks[i].offset;
		cells[base + i].flags = 0;
		cells[base + i].lock = apbc_gate_clks[i].lock;
		cells[base + i].bits = 0x4;
	}

	base = nr_resets_apbc;
	for (i = 0; i < nr_resets_apbcp; i++) {
		cells[base + i].clk_id = apbcp_gate_clks[i].id;
		cells[base + i].reg =
			pxa_unit->apbc_base + apbc_gate_clks[i].offset;
		cells[base + i].flags = 0;
		cells[base + i].lock = apbc_gate_clks[i].lock;
		cells[base + i].bits = 0x4;
	}

	mmp_clk_reset_register(np, cells, nr_resets);
}