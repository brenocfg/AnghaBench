#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct aibs_softc {int /*<<< orphan*/  sc_dev; struct aibs_sensor* sc_asens_fan; struct aibs_sensor* sc_asens_temp; struct aibs_sensor* sc_asens_volt; int /*<<< orphan*/  sc_ah; struct sysctl_oid* sc_fan_sysctl; struct sysctl_oid* sc_temp_sysctl; struct sysctl_oid* sc_volt_sysctl; } ;
struct aibs_sensor {int dummy; } ;
struct TYPE_11__ {TYPE_3__* Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_9__ {int Count; TYPE_3__* Elements; } ;
struct TYPE_8__ {int Value; } ;
struct TYPE_10__ {scalar_t__ Type; TYPE_2__ Package; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
#define  AIBS_SENS_TYPE_FAN 130 
#define  AIBS_SENS_TYPE_TEMP 129 
#define  AIBS_SENS_TYPE_VOLT 128 
 int /*<<< orphan*/  AcpiEvaluateObjectTyped (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_3__*) ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int aibs_add_sensor (struct aibs_softc*,TYPE_3__*,struct aibs_sensor*,char const**) ; 
 int /*<<< orphan*/  aibs_sensor_added (struct aibs_softc*,struct sysctl_oid*,char const*,int,struct aibs_sensor*,char const*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 struct aibs_sensor* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
aibs_attach_sif(struct aibs_softc *sc, int st)
{
	char			name[] = "?SIF";
	ACPI_STATUS		s;
	ACPI_BUFFER		b;
	ACPI_OBJECT		*bp, *o;
	const char		*node;
	struct aibs_sensor	*as;
	struct sysctl_oid	**so;
	int			i, n;
	int err;

	switch (st) {
	case AIBS_SENS_TYPE_VOLT:
		node = "volt";
		name[0] = 'V';
		so = &sc->sc_volt_sysctl;
		break;
	case AIBS_SENS_TYPE_TEMP:
		node = "temp";
		name[0] = 'T';
		so = &sc->sc_temp_sysctl;
		break;
	case AIBS_SENS_TYPE_FAN:
		node = "fan";
		name[0] = 'F';
		so = &sc->sc_fan_sysctl;
		break;
	default:
		panic("Unsupported sensor type %d", st);
	}

	b.Length = ACPI_ALLOCATE_BUFFER;
	s = AcpiEvaluateObjectTyped(sc->sc_ah, name, NULL, &b,
	    ACPI_TYPE_PACKAGE);
	if (ACPI_FAILURE(s)) {
		device_printf(sc->sc_dev, "%s not found\n", name);
		return (ENXIO);
	}

	bp = b.Pointer;
	o = bp->Package.Elements;
	if (o[0].Type != ACPI_TYPE_INTEGER) {
		device_printf(sc->sc_dev, "%s[0]: invalid type\n", name);
		AcpiOsFree(b.Pointer);
		return (ENXIO);
	}

	n = o[0].Integer.Value;
	if (bp->Package.Count - 1 < n) {
		device_printf(sc->sc_dev, "%s: invalid package\n", name);
		AcpiOsFree(b.Pointer);
		return (ENXIO);
	} else if (bp->Package.Count - 1 > n) {
		int on = n;

#ifdef AIBS_MORE_SENSORS
		n = bp->Package.Count - 1;
#endif
		device_printf(sc->sc_dev, "%s: malformed package: %i/%i"
		    ", assume %i\n", name, on, bp->Package.Count - 1, n);
	}
	if (n < 1) {
		device_printf(sc->sc_dev, "%s: no members in the package\n",
		    name);
		AcpiOsFree(b.Pointer);
		return (ENXIO);
	}

	as = malloc(sizeof(*as) * n, M_DEVBUF, M_WAITOK | M_ZERO);
	switch (st) {
	case AIBS_SENS_TYPE_VOLT:
		sc->sc_asens_volt = as;
		break;
	case AIBS_SENS_TYPE_TEMP:
		sc->sc_asens_temp = as;
		break;
	case AIBS_SENS_TYPE_FAN:
		sc->sc_asens_fan = as;
		break;
	}

	/* sysctl subtree for sensors of this type */
	*so = SYSCTL_ADD_NODE(device_get_sysctl_ctx(sc->sc_dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->sc_dev)), st,
	    node, CTLFLAG_RD, NULL, NULL);

	for (i = 0, o++; i < n; i++, o++) {
		const char	*descr;

		err = aibs_add_sensor(sc, o, &as[i], &descr);
		if (err == 0)
			aibs_sensor_added(sc, *so, node, i, &as[i], descr);
	}

	AcpiOsFree(b.Pointer);
	return (0);
}