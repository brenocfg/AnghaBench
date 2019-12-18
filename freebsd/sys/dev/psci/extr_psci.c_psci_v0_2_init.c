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
struct psci_softc {int psci_version; int /*<<< orphan*/ * psci_fnids; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct psci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSCI_FNID_AFFINITY_INFO ; 
 int /*<<< orphan*/  PSCI_FNID_CPU_OFF ; 
 int /*<<< orphan*/  PSCI_FNID_CPU_ON ; 
 int /*<<< orphan*/  PSCI_FNID_CPU_SUSPEND ; 
 int /*<<< orphan*/  PSCI_FNID_MIGRATE ; 
 int /*<<< orphan*/  PSCI_FNID_MIGRATE_INFO_TYPE ; 
 int /*<<< orphan*/  PSCI_FNID_MIGRATE_INFO_UP_CPU ; 
 int /*<<< orphan*/  PSCI_FNID_SYSTEM_OFF ; 
 int /*<<< orphan*/  PSCI_FNID_SYSTEM_RESET ; 
 int /*<<< orphan*/  PSCI_FNID_VERSION ; 
 size_t PSCI_FN_AFFINITY_INFO ; 
 size_t PSCI_FN_CPU_OFF ; 
 size_t PSCI_FN_CPU_ON ; 
 size_t PSCI_FN_CPU_SUSPEND ; 
 size_t PSCI_FN_MIGRATE ; 
 size_t PSCI_FN_MIGRATE_INFO_TYPE ; 
 size_t PSCI_FN_MIGRATE_INFO_UP_CPU ; 
 size_t PSCI_FN_SYSTEM_OFF ; 
 size_t PSCI_FN_SYSTEM_RESET ; 
 size_t PSCI_FN_VERSION ; 
 int PSCI_RETVAL_NOT_SUPPORTED ; 
 int PSCI_VER_MAJOR (int) ; 
 int PSCI_VER_MINOR (int) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int _psci_get_version (struct psci_softc*) ; 
 scalar_t__ bootverbose ; 
 struct psci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  psci_shutdown ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static int
psci_v0_2_init(device_t dev, int default_version)
{
	struct psci_softc *sc = device_get_softc(dev);
	int version;

	/* PSCI v0.2 specifies explicit function IDs. */
	sc->psci_fnids[PSCI_FN_VERSION]		    = PSCI_FNID_VERSION;
	sc->psci_fnids[PSCI_FN_CPU_SUSPEND]	    = PSCI_FNID_CPU_SUSPEND;
	sc->psci_fnids[PSCI_FN_CPU_OFF]		    = PSCI_FNID_CPU_OFF;
	sc->psci_fnids[PSCI_FN_CPU_ON]		    = PSCI_FNID_CPU_ON;
	sc->psci_fnids[PSCI_FN_AFFINITY_INFO]	    = PSCI_FNID_AFFINITY_INFO;
	sc->psci_fnids[PSCI_FN_MIGRATE]		    = PSCI_FNID_MIGRATE;
	sc->psci_fnids[PSCI_FN_MIGRATE_INFO_TYPE]   = PSCI_FNID_MIGRATE_INFO_TYPE;
	sc->psci_fnids[PSCI_FN_MIGRATE_INFO_UP_CPU] = PSCI_FNID_MIGRATE_INFO_UP_CPU;
	sc->psci_fnids[PSCI_FN_SYSTEM_OFF]	    = PSCI_FNID_SYSTEM_OFF;
	sc->psci_fnids[PSCI_FN_SYSTEM_RESET]	    = PSCI_FNID_SYSTEM_RESET;

	version = _psci_get_version(sc);

	/*
	 * U-Boot PSCI implementation doesn't have psci_get_version()
	 * method implemented for many boards. In this case, use the version
	 * readed from FDT as fallback. No fallback method for ACPI.
	 */
	if (version == PSCI_RETVAL_NOT_SUPPORTED) {
		if (default_version == PSCI_RETVAL_NOT_SUPPORTED)
			return (1);

		version = default_version;
		printf("PSCI get_version() function is not implemented, "
		    " assuming v%d.%d\n", PSCI_VER_MAJOR(version),
		    PSCI_VER_MINOR(version));
	}

	sc->psci_version = version;
	if ((PSCI_VER_MAJOR(version) == 0 && PSCI_VER_MINOR(version) == 2) ||
	    PSCI_VER_MAJOR(version) == 1) {
		if (bootverbose)
			device_printf(dev, "PSCI version 0.2 compatible\n");

		/*
		 * We only register this for v0.2 since v0.1 doesn't support
		 * system_reset.
		 */
		EVENTHANDLER_REGISTER(shutdown_final, psci_shutdown, sc,
		    SHUTDOWN_PRI_LAST);

		return (0);
	}

	device_printf(dev, "PSCI version number mismatched with DT\n");
	return (1);
}