#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rk_cru_softc {int ngates; int /*<<< orphan*/  clkdom; TYPE_2__* gates; } ;
struct TYPE_3__ {int parent_cnt; int /*<<< orphan*/ * parent_names; int /*<<< orphan*/ * name; int /*<<< orphan*/  id; } ;
struct rk_clk_gate_def {int mask; int off_value; scalar_t__ on_value; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; TYPE_1__ clkdef; } ;
typedef  int /*<<< orphan*/  def ;
struct TYPE_4__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  parent_name; int /*<<< orphan*/ * name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct rk_clk_gate_def*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_clk_gate_register (int /*<<< orphan*/ ,struct rk_clk_gate_def*) ; 

__attribute__((used)) static int
rk_cru_register_gates(struct rk_cru_softc *sc)
{
	struct rk_clk_gate_def def;
	int i;

	for (i = 0; i < sc->ngates; i++) {
		if (sc->gates[i].name == NULL)
			continue;
		memset(&def, 0, sizeof(def));
		def.clkdef.id = sc->gates[i].id;
		def.clkdef.name = sc->gates[i].name;
		def.clkdef.parent_names = &sc->gates[i].parent_name;
		def.clkdef.parent_cnt = 1;
		def.offset = sc->gates[i].offset;
		def.shift = sc->gates[i].shift;
		def.mask = 1;
		def.on_value = 0;
		def.off_value = 1;
		rk_clk_gate_register(sc->clkdom, &def);
	}

	return (0);
}