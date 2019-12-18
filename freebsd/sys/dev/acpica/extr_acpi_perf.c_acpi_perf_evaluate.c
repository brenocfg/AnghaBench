#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct acpi_px {int dummy; } ;
struct acpi_perf_softc {int px_count; scalar_t__ px_rid; int /*<<< orphan*/ * perf_status; int /*<<< orphan*/  perf_sts_type; int /*<<< orphan*/  dev; int /*<<< orphan*/ * perf_ctrl; int /*<<< orphan*/  perf_ctrl_type; TYPE_4__* px_states; int /*<<< orphan*/  handle; void* info_only; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_13__ {int core_freq; } ;
struct TYPE_12__ {int /*<<< orphan*/ * Pointer; void* Length; } ;
struct TYPE_10__ {int Count; TYPE_2__* Elements; } ;
struct TYPE_11__ {TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 void* ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (TYPE_2__*,int) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_perf_softc*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  M_ACPIPERF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* TRUE ; 
 int acpi_PkgGas (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_PkgInt32 (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  acpi_px_available (struct acpi_perf_softc*) ; 
 int /*<<< orphan*/  acpi_px_notify ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct acpi_perf_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_perf_evaluate(device_t dev)
{
	struct acpi_perf_softc *sc;
	ACPI_BUFFER buf;
	ACPI_OBJECT *pkg, *res;
	ACPI_STATUS status;
	int count, error, i, j;
	static int once = 1;
	uint32_t *p;

	/* Get the control values and parameters for each state. */
	error = ENXIO;
	sc = device_get_softc(dev);
	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	status = AcpiEvaluateObject(sc->handle, "_PSS", NULL, &buf);
	if (ACPI_FAILURE(status))
		return (ENXIO);

	pkg = (ACPI_OBJECT *)buf.Pointer;
	if (!ACPI_PKG_VALID(pkg, 1)) {
		device_printf(dev, "invalid top level _PSS package\n");
		goto out;
	}
	sc->px_count = pkg->Package.Count;

	sc->px_states = malloc(sc->px_count * sizeof(struct acpi_px),
	    M_ACPIPERF, M_WAITOK | M_ZERO);

	/*
	 * Each state is a package of {CoreFreq, Power, TransitionLatency,
	 * BusMasterLatency, ControlVal, StatusVal}, sorted from highest
	 * performance to lowest.
	 */
	count = 0;
	for (i = 0; i < sc->px_count; i++) {
		res = &pkg->Package.Elements[i];
		if (!ACPI_PKG_VALID(res, 6)) {
			if (once) {
				once = 0;
				device_printf(dev, "invalid _PSS package\n");
			}
			continue;
		}

		/* Parse the rest of the package into the struct. */
		p = &sc->px_states[count].core_freq;
		for (j = 0; j < 6; j++, p++)
			acpi_PkgInt32(res, j, p);

		/*
		 * Check for some impossible frequencies that some systems
		 * use to indicate they don't actually support this Px state.
		 */
		if (sc->px_states[count].core_freq == 0 ||
		    sc->px_states[count].core_freq == 9999 ||
		    sc->px_states[count].core_freq == 0x9999 ||
		    sc->px_states[count].core_freq >= 0xffff)
			continue;

		/* Check for duplicate entries */
		if (count > 0 &&
		    sc->px_states[count - 1].core_freq ==
			sc->px_states[count].core_freq)
			continue;

		count++;
	}
	sc->px_count = count;

	/* No valid Px state found so give up. */
	if (count == 0)
		goto out;
	AcpiOsFree(buf.Pointer);

	/* Get the control and status registers (one of each). */
	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	status = AcpiEvaluateObject(sc->handle, "_PCT", NULL, &buf);
	if (ACPI_FAILURE(status))
		goto out;

	/* Check the package of two registers, each a Buffer in GAS format. */
	pkg = (ACPI_OBJECT *)buf.Pointer;
	if (!ACPI_PKG_VALID(pkg, 2)) {
		device_printf(dev, "invalid perf register package\n");
		goto out;
	}

	error = acpi_PkgGas(sc->dev, pkg, 0, &sc->perf_ctrl_type, &sc->px_rid,
	    &sc->perf_ctrl, 0);
	if (error) {
		/*
		 * If the register is of type FFixedHW, we can only return
		 * info, we can't get or set new settings.
		 */
		if (error == EOPNOTSUPP) {
			sc->info_only = TRUE;
			error = 0;
		} else
			device_printf(dev, "failed in PERF_CTL attach\n");
		goto out;
	}
	sc->px_rid++;

	error = acpi_PkgGas(sc->dev, pkg, 1, &sc->perf_sts_type, &sc->px_rid,
	    &sc->perf_status, 0);
	if (error) {
		if (error == EOPNOTSUPP) {
			sc->info_only = TRUE;
			error = 0;
		} else
			device_printf(dev, "failed in PERF_STATUS attach\n");
		goto out;
	}
	sc->px_rid++;

	/* Get our current limit and register for notifies. */
	acpi_px_available(sc);
	AcpiInstallNotifyHandler(sc->handle, ACPI_DEVICE_NOTIFY,
	    acpi_px_notify, sc);
	error = 0;

out:
	if (error) {
		if (sc->px_states) {
			free(sc->px_states, M_ACPIPERF);
			sc->px_states = NULL;
		}
		if (sc->perf_ctrl) {
			bus_release_resource(sc->dev, sc->perf_ctrl_type, 0,
			    sc->perf_ctrl);
			bus_delete_resource(sc->dev, sc->perf_ctrl_type, 0);
			sc->perf_ctrl = NULL;
		}
		if (sc->perf_status) {
			bus_release_resource(sc->dev, sc->perf_sts_type, 1,
			    sc->perf_status);
			bus_delete_resource(sc->dev, sc->perf_sts_type, 1);
			sc->perf_status = NULL;
		}
		sc->px_rid = 0;
		sc->px_count = 0;
	}
	if (buf.Pointer)
		AcpiOsFree(buf.Pointer);
	return (error);
}