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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct mv_thermal_softc {int cur_sensor; struct mv_thermal_config* config; int /*<<< orphan*/ * syscon; int /*<<< orphan*/  dev; int /*<<< orphan*/  mtx; } ;
struct mv_thermal_config {int type; int ncpus; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
#define  MV_AP806 129 
#define  MV_CP110 128 
 int /*<<< orphan*/  OID_AUTO ; 
 scalar_t__ SYSCON_GET_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap806_init (struct mv_thermal_softc*) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  cp110_init (struct mv_thermal_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct mv_thermal_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_thermal_sysctl ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
mv_thermal_attach(device_t dev)
{
	struct mv_thermal_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *oid;
	phandle_t node;
	char name[255];
	char desc[255];
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	sc->config = (struct mv_thermal_config *)
	    ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);


	if (SYSCON_GET_HANDLE(sc->dev, &sc->syscon) != 0 ||
	    sc->syscon == NULL) {
		device_printf(dev, "cannot get syscon for device\n");
		return (ENXIO);
	}

	sc->cur_sensor = -1;
	switch (sc->config->type) {
	case MV_AP806:
		ap806_init(sc);
		break;
	case MV_CP110:
		cp110_init(sc);
		break;
	}

	ctx = device_get_sysctl_ctx(dev);
	oid = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	/* There is always at least one sensor */
	SYSCTL_ADD_PROC(ctx, oid, OID_AUTO, "internal",
	    CTLTYPE_INT | CTLFLAG_RD,
	    dev, 0, mv_thermal_sysctl,
	    "IK",
	    "Internal Temperature");

	for (i = 0; i < sc->config->ncpus; i++) {
		snprintf(name, sizeof(name), "cpu%d", i);
		snprintf(desc, sizeof(desc), "CPU%d Temperature", i);
		SYSCTL_ADD_PROC(ctx, oid, OID_AUTO, name,
		    CTLTYPE_INT | CTLFLAG_RD,
		    dev, i + 1, mv_thermal_sysctl,
		    "IK",
		    desc);
	}

	return (0);
}