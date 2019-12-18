#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct aibs_softc {int /*<<< orphan*/  sc_dev; struct sysctl_oid* sc_fan_sysctl; struct sysctl_oid* sc_temp_sysctl; struct sysctl_oid* sc_volt_sysctl; struct aibs_sensor* sc_asens_all; int /*<<< orphan*/  sc_ah; } ;
struct aibs_sensor {int t; } ;
struct TYPE_13__ {TYPE_4__* Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_10__ {int Count; int /*<<< orphan*/ * Elements; } ;
struct TYPE_9__ {int /*<<< orphan*/  Value; } ;
struct TYPE_12__ {TYPE_2__ Package; int /*<<< orphan*/  Type; TYPE_1__ Integer; } ;
struct TYPE_11__ {int Count; TYPE_4__* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT_LIST ;
typedef  TYPE_4__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_5__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AIBS_GROUP_SENSORS ; 
#define  AIBS_SENS_TYPE_FAN 130 
#define  AIBS_SENS_TYPE_TEMP 129 
#define  AIBS_SENS_TYPE_VOLT 128 
 int /*<<< orphan*/  AcpiEvaluateObjectTyped (int /*<<< orphan*/ ,char*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_4__*) ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int aibs_add_sensor (struct aibs_softc*,int /*<<< orphan*/ *,struct aibs_sensor*,char const**) ; 
 int /*<<< orphan*/  aibs_sensor_added (struct aibs_softc*,struct sysctl_oid*,char const*,int,struct aibs_sensor*,char const*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct aibs_sensor* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
aibs_attach_ggrp(struct aibs_softc *sc)
{
	ACPI_STATUS		s;
	ACPI_BUFFER		buf;
	ACPI_HANDLE		h;
	ACPI_OBJECT		id;
	ACPI_OBJECT		*bp;
	ACPI_OBJECT_LIST	arg;
	int			i;
	int			t, v, f;
	int			err;
	int			*s_idx;
	const char		*name;
	const char		*descr;
	struct aibs_sensor	*sensor;
	struct sysctl_oid	**so;

	/* First see if GITM is available. */
	s = AcpiGetHandle(sc->sc_ah, "GITM", &h);
	if (ACPI_FAILURE(s)) {
		if (bootverbose)
			device_printf(sc->sc_dev, "GITM not found\n");
		return (ENXIO);
	}

	/*
	 * Now call GGRP with the appropriate argument to list sensors.
	 * The method lists different groups of entities depending on
	 * the argument.
	 */
	id.Integer.Value = AIBS_GROUP_SENSORS;
	id.Type = ACPI_TYPE_INTEGER;
	arg.Count = 1;
	arg.Pointer = &id;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	buf.Pointer = NULL;
	s = AcpiEvaluateObjectTyped(sc->sc_ah, "GGRP", &arg, &buf,
	    ACPI_TYPE_PACKAGE);
	if (ACPI_FAILURE(s)) {
		device_printf(sc->sc_dev, "GGRP not found\n");
		return (ENXIO);
	}

	bp = buf.Pointer;
	sc->sc_asens_all = malloc(sizeof(*sc->sc_asens_all) * bp->Package.Count,
	    M_DEVBUF, M_WAITOK | M_ZERO);
	v = t = f = 0;
	for (i = 0; i < bp->Package.Count; i++) {
		sensor = &sc->sc_asens_all[i];
		err = aibs_add_sensor(sc, &bp->Package.Elements[i], sensor,
		    &descr);
		if (err != 0)
			continue;

		switch (sensor->t) {
		case AIBS_SENS_TYPE_VOLT:
			name = "volt";
			so = &sc->sc_volt_sysctl;
			s_idx = &v;
			break;
		case AIBS_SENS_TYPE_TEMP:
			name = "temp";
			so = &sc->sc_temp_sysctl;
			s_idx = &t;
			break;
		case AIBS_SENS_TYPE_FAN:
			name = "fan";
			so = &sc->sc_fan_sysctl;
			s_idx = &f;
			break;
		default:
			panic("add_sensor succeeded for unknown sensor type %d",
			    sensor->t);
		}

		if (*so == NULL) {
			/* sysctl subtree for sensors of this type */
			*so = SYSCTL_ADD_NODE(device_get_sysctl_ctx(sc->sc_dev),
			    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->sc_dev)),
			    sensor->t, name, CTLFLAG_RD, NULL, NULL);
		}
		aibs_sensor_added(sc, *so, name, *s_idx, sensor, descr);
		*s_idx += 1;
	}

	AcpiOsFree(buf.Pointer);
	return (0);
}