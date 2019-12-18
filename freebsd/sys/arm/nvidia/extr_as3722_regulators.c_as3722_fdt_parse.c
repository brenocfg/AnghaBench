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
typedef  int /*<<< orphan*/  supply_node ;
struct reg_def {char* supply_name; } ;
struct as3722_softc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent_name; } ;
struct as3722_regnode_init_def {int ext_control; int enable_tracking; TYPE_1__ reg_init_def; } ;
typedef  int /*<<< orphan*/  prop_name ;
typedef  int phandle_t ;

/* Variables and functions */
 int OF_getencprop (int,char*,int*,int) ; 
 int OF_getprop_alloc (int,char*,void**) ; 
 scalar_t__ OF_hasprop (int,char*) ; 
 int OF_node_from_xref (int) ; 
 int OF_parent (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_parse_ofw_stdparam (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
as3722_fdt_parse(struct as3722_softc *sc, phandle_t node, struct reg_def *def,
struct as3722_regnode_init_def *init_def)
{
	int rv;
	phandle_t parent, supply_node;
	char prop_name[64]; /* Maximum OFW property name length. */

	rv = regulator_parse_ofw_stdparam(sc->dev, node,
	    &init_def->reg_init_def);

	rv = OF_getencprop(node, "ams,ext-control", &init_def->ext_control,
	    sizeof(init_def->ext_control));
	if (rv <= 0)
		init_def->ext_control = 0;
	if (init_def->ext_control > 3) {
		device_printf(sc->dev,
		    "Invalid value for ams,ext-control property: %d\n",
		    init_def->ext_control);
		init_def->ext_control = 0;
	}
	if (OF_hasprop(node, "ams,enable-tracking"))
		init_def->enable_tracking = 1;


	/* Get parent supply. */
	if (def->supply_name == NULL)
		 return;

	parent = OF_parent(node);
	snprintf(prop_name, sizeof(prop_name), "%s-supply",
	    def->supply_name);
	rv = OF_getencprop(parent, prop_name, &supply_node,
	    sizeof(supply_node));
	if (rv <= 0)
		return;
	supply_node = OF_node_from_xref(supply_node);
	rv = OF_getprop_alloc(supply_node, "regulator-name",
	    (void **)&init_def->reg_init_def.parent_name);
	if (rv <= 0)
		init_def->reg_init_def.parent_name = NULL;
}