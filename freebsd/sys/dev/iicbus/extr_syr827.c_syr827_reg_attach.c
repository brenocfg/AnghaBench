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
typedef  int /*<<< orphan*/  uint32_t ;
struct syr827_reg_sc {void* volt_reg; void* suspend_reg; int /*<<< orphan*/  param; int /*<<< orphan*/  xref; int /*<<< orphan*/  base_dev; struct regnode* regnode; } ;
struct regnode_init_def {int /*<<< orphan*/  ofw_node; scalar_t__ id; } ;
struct regnode {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  initdef ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 void* VSEL0 ; 
 void* VSEL1 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct regnode_init_def*,int /*<<< orphan*/ ,int) ; 
 struct regnode* regnode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regnode_init_def*) ; 
 struct syr827_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  regnode_get_stdparam (struct regnode*) ; 
 int /*<<< orphan*/  regnode_register (struct regnode*) ; 
 int /*<<< orphan*/  regulator_parse_ofw_stdparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regnode_init_def*) ; 
 int /*<<< orphan*/  syr827_regnode_class ; 

__attribute__((used)) static struct syr827_reg_sc *
syr827_reg_attach(device_t dev, phandle_t node)
{
	struct syr827_reg_sc *reg_sc;
	struct regnode_init_def initdef;
	struct regnode *regnode;
	int suspend_reg;

	memset(&initdef, 0, sizeof(initdef));
	regulator_parse_ofw_stdparam(dev, node, &initdef);
	initdef.id = 0;
	initdef.ofw_node = node;
	regnode = regnode_create(dev, &syr827_regnode_class, &initdef);
	if (regnode == NULL) {
		device_printf(dev, "cannot create regulator\n");
		return (NULL);
	}

	reg_sc = regnode_get_softc(regnode);
	reg_sc->regnode = regnode;
	reg_sc->base_dev = dev;
	reg_sc->xref = OF_xref_from_node(node);
	reg_sc->param = regnode_get_stdparam(regnode);

	if (OF_getencprop(node, "fcs,suspend-voltage-selector", &suspend_reg,
	    sizeof(uint32_t)) <= 0)
		suspend_reg = 0;

	switch (suspend_reg) {
	case 0:
		reg_sc->suspend_reg = VSEL0;
		reg_sc->volt_reg = VSEL1;
		break;
	case 1:
		reg_sc->suspend_reg = VSEL1;
		reg_sc->volt_reg = VSEL0;
		break;
	}

	regnode_register(regnode);

	return (reg_sc);
}