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
struct TYPE_3__ {int id; int parent_cnt; int /*<<< orphan*/ * parent_names; int /*<<< orphan*/ * name; } ;
struct clk_gate_def {int mask; int on_value; scalar_t__ off_value; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; TYPE_1__ clkdef; } ;
struct aw_ccung_softc {int ngates; int /*<<< orphan*/  clkdom; TYPE_2__* gates; } ;
typedef  int /*<<< orphan*/  def ;
struct TYPE_4__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  parent_name; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clknode_gate_register (int /*<<< orphan*/ ,struct clk_gate_def*) ; 
 int /*<<< orphan*/  memset (struct clk_gate_def*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aw_ccung_register_gates(struct aw_ccung_softc *sc)
{
	struct clk_gate_def def;
	int i;

	for (i = 0; i < sc->ngates; i++) {
		if (sc->gates[i].name == NULL)
			continue;
		memset(&def, 0, sizeof(def));
		def.clkdef.id = i;
		def.clkdef.name = sc->gates[i].name;
		def.clkdef.parent_names = &sc->gates[i].parent_name;
		def.clkdef.parent_cnt = 1;
		def.offset = sc->gates[i].offset;
		def.shift = sc->gates[i].shift;
		def.mask = 1;
		def.on_value = 1;
		def.off_value = 0;
		clknode_gate_register(sc->clkdom, &def);
	}

	return (0);
}