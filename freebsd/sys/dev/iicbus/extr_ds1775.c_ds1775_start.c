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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_2__ {char zone; char* name; int (* read ) (struct pmac_therm*) ;void* max_temp; void* target_temp; } ;
struct ds1775_softc {int /*<<< orphan*/  enum_hook; TYPE_1__ sc_sensor; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 void* ZERO_C_TO_K ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct ds1775_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 scalar_t__ ds1775_sensor_read ; 
 int /*<<< orphan*/  ds1775_sensor_sysctl ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_thermal_sensor_register (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char tolower (char) ; 

__attribute__((used)) static void
ds1775_start(void *xdev)
{
	phandle_t child;
	struct ds1775_softc *sc;
	struct sysctl_oid *oid, *sensroot_oid;
	struct sysctl_ctx_list *ctx;
	ssize_t plen;
	int i;
	char sysctl_name[40], sysctl_desc[40];

	device_t dev = (device_t)xdev;

	sc = device_get_softc(dev);

	child = ofw_bus_get_node(dev);

	ctx = device_get_sysctl_ctx(dev);
	sensroot_oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO, "sensor",
	    CTLFLAG_RD, 0, "DS1775 Sensor Information");

	if (OF_getprop(child, "hwsensor-zone", &sc->sc_sensor.zone,
		       sizeof(int)) < 0)
		sc->sc_sensor.zone = 0;

	plen = OF_getprop(child, "hwsensor-location", sc->sc_sensor.name,
			  sizeof(sc->sc_sensor.name));

	if (plen == -1) {
		strcpy(sysctl_name, "sensor");
	} else {
		for (i = 0; i < strlen(sc->sc_sensor.name); i++) {
			sysctl_name[i] = tolower(sc->sc_sensor.name[i]);
			if (isspace(sysctl_name[i]))
				sysctl_name[i] = '_';
		}
		sysctl_name[i] = 0;
	}

	/* Make up target temperatures. These are low, for the drive bay. */
	if (sc->sc_sensor.zone == 0) {
		sc->sc_sensor.target_temp = 500 + ZERO_C_TO_K;
		sc->sc_sensor.max_temp = 600 + ZERO_C_TO_K;
	}
	else {
		sc->sc_sensor.target_temp = 300 + ZERO_C_TO_K;
		sc->sc_sensor.max_temp = 600 + ZERO_C_TO_K;
	}

	sc->sc_sensor.read =
	    (int (*)(struct pmac_therm *sc))(ds1775_sensor_read);
	pmac_thermal_sensor_register(&sc->sc_sensor);

	sprintf(sysctl_desc,"%s %s", sc->sc_sensor.name, "(C)");
	oid = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(sensroot_oid),
			      OID_AUTO, sysctl_name, CTLFLAG_RD, 0,
			      "Sensor Information");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(oid), OID_AUTO, "temp",
			CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, dev,
			0, ds1775_sensor_sysctl, "IK", sysctl_desc);

	config_intrhook_disestablish(&sc->enum_hook);
}