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
struct rk805_regdef {scalar_t__ voltage_min; scalar_t__ voltage_max; int /*<<< orphan*/  id; } ;
struct rk805_reg_sc {int /*<<< orphan*/  param; int /*<<< orphan*/  xref; struct rk805_regdef* def; int /*<<< orphan*/  base_dev; struct regnode* regnode; } ;
struct TYPE_2__ {scalar_t__ min_uvolt; scalar_t__ max_uvolt; } ;
struct regnode_init_def {int /*<<< orphan*/  ofw_node; int /*<<< orphan*/  id; TYPE_1__ std_param; } ;
struct regnode {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  initdef ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct regnode_init_def*,int /*<<< orphan*/ ,int) ; 
 struct regnode* regnode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regnode_init_def*) ; 
 struct rk805_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  regnode_get_stdparam (struct regnode*) ; 
 int /*<<< orphan*/  regnode_register (struct regnode*) ; 
 scalar_t__ regulator_parse_ofw_stdparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regnode_init_def*) ; 
 int /*<<< orphan*/  rk805_regnode_class ; 

__attribute__((used)) static struct rk805_reg_sc *
rk805_reg_attach(device_t dev, phandle_t node,
    struct rk805_regdef *def)
{
	struct rk805_reg_sc *reg_sc;
	struct regnode_init_def initdef;
	struct regnode *regnode;

	memset(&initdef, 0, sizeof(initdef));
	if (regulator_parse_ofw_stdparam(dev, node, &initdef) != 0) {
		device_printf(dev, "cannot create regulator\n");
		return (NULL);
	}
	if (initdef.std_param.min_uvolt == 0)
		initdef.std_param.min_uvolt = def->voltage_min;
	if (initdef.std_param.max_uvolt == 0)
		initdef.std_param.max_uvolt = def->voltage_max;
	initdef.id = def->id;
	initdef.ofw_node = node;

	regnode = regnode_create(dev, &rk805_regnode_class, &initdef);
	if (regnode == NULL) {
		device_printf(dev, "cannot create regulator\n");
		return (NULL);
	}

	reg_sc = regnode_get_softc(regnode);
	reg_sc->regnode = regnode;
	reg_sc->base_dev = dev;
	reg_sc->def = def;
	reg_sc->xref = OF_xref_from_node(node);
	reg_sc->param = regnode_get_stdparam(regnode);

	regnode_register(regnode);

	return (reg_sc);
}