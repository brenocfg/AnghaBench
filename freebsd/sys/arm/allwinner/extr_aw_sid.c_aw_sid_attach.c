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
struct aw_sid_softc {struct aw_sid_conf* sid_conf; int /*<<< orphan*/  prctl_mtx; int /*<<< orphan*/  res; int /*<<< orphan*/  sid_dev; } ;
struct aw_sid_conf {int nfuses; TYPE_1__* efuses; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ ocd_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct aw_sid_softc* aw_sid_sc ; 
 int /*<<< orphan*/  aw_sid_spec ; 
 int /*<<< orphan*/  aw_sid_sysctl ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct aw_sid_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_2__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_sid_attach(device_t dev)
{
	struct aw_sid_softc *sc;
	phandle_t node;
	int i;

	node = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);
	sc->sid_dev = dev;

	if (bus_alloc_resources(dev, aw_sid_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	mtx_init(&sc->prctl_mtx, device_get_nameunit(dev), NULL, MTX_DEF);
	sc->sid_conf = (struct aw_sid_conf *)ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	aw_sid_sc = sc;

	/* Register ourself so device can resolve who we are */
	OF_device_register_xref(OF_xref_from_node(node), dev);

	for (i = 0; i < sc->sid_conf->nfuses ;i++) {\
		SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
		    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		    OID_AUTO, sc->sid_conf->efuses[i].name,
		    CTLTYPE_STRING | CTLFLAG_RD,
		    dev, sc->sid_conf->efuses[i].id, aw_sid_sysctl,
		    "A", sc->sid_conf->efuses[i].desc);
	}
	return (0);
}