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
struct sy8106a_reg_sc {int /*<<< orphan*/  param; int /*<<< orphan*/  xref; int /*<<< orphan*/  base_dev; struct regnode* regnode; } ;
struct regnode_init_def {int /*<<< orphan*/  ofw_node; scalar_t__ id; } ;
struct regnode {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  initdef ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct regnode_init_def*,int /*<<< orphan*/ ,int) ; 
 struct regnode* regnode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regnode_init_def*) ; 
 struct sy8106a_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  regnode_get_stdparam (struct regnode*) ; 
 int /*<<< orphan*/  regnode_register (struct regnode*) ; 
 int /*<<< orphan*/  regulator_parse_ofw_stdparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regnode_init_def*) ; 
 int /*<<< orphan*/  sy8106a_regnode_class ; 

__attribute__((used)) static struct sy8106a_reg_sc *
sy8106a_reg_attach(device_t dev, phandle_t node)
{
	struct sy8106a_reg_sc *reg_sc;
	struct regnode_init_def initdef;
	struct regnode *regnode;

	memset(&initdef, 0, sizeof(initdef));
	regulator_parse_ofw_stdparam(dev, node, &initdef);
	initdef.id = 0;
	initdef.ofw_node = node;
	regnode = regnode_create(dev, &sy8106a_regnode_class, &initdef);
	if (regnode == NULL) {
		device_printf(dev, "cannot create regulator\n");
		return (NULL);
	}

	reg_sc = regnode_get_softc(regnode);
	reg_sc->regnode = regnode;
	reg_sc->base_dev = dev;
	reg_sc->xref = OF_xref_from_node(node);
	reg_sc->param = regnode_get_stdparam(regnode);

	regnode_register(regnode);

	return (reg_sc);
}