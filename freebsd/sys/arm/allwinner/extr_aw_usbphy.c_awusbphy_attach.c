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
struct phynode_init_def {int id; int /*<<< orphan*/  ofw_node; } ;
struct phynode {int dummy; } ;
struct awusbphy_softc {TYPE_1__* phy_conf; } ;
typedef  int /*<<< orphan*/  phy_init ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int num_phys; } ;

/* Variables and functions */
 int ENXIO ; 
 int awusbphy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  awusbphy_phynode_class ; 
 int /*<<< orphan*/  bzero (struct phynode_init_def*,int) ; 
 struct awusbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 

__attribute__((used)) static int
awusbphy_attach(device_t dev)
{
	int error;
	struct phynode *phynode;
	struct phynode_init_def phy_init;
	struct awusbphy_softc *sc;
	int i;

	sc = device_get_softc(dev);
	error = awusbphy_init(dev);
	if (error) {
		device_printf(dev, "failed to initialize USB PHY, error %d\n",
		    error);
		return (error);
	}

	/* Create and register phys. */
	for (i = 0; i < sc->phy_conf->num_phys; i++) {
		bzero(&phy_init, sizeof(phy_init));
		phy_init.id = i;
		phy_init.ofw_node = ofw_bus_get_node(dev);
		phynode = phynode_create(dev, &awusbphy_phynode_class,
		    &phy_init);
		if (phynode == NULL) {
			device_printf(dev, "failed to create USB PHY\n");
			return (ENXIO);
		}
		if (phynode_register(phynode) == NULL) {
			device_printf(dev, "failed to create USB PHY\n");
			return (ENXIO);
		}
	}

	return (error);
}