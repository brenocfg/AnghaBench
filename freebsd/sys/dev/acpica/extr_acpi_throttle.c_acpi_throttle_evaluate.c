#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct acpi_throttle_softc {int cpu_p_blk_len; int /*<<< orphan*/  cpu_dev; int /*<<< orphan*/  cpu_p_blk; int /*<<< orphan*/ * cpu_p_cnt; int /*<<< orphan*/  cpu_p_type; int /*<<< orphan*/  cpu_handle; } ;
typedef  int /*<<< orphan*/  obj ;
typedef  int /*<<< orphan*/  gas ;
struct TYPE_13__ {int DutyOffset; scalar_t__ DutyWidth; } ;
struct TYPE_12__ {int Length; TYPE_2__* Pointer; } ;
struct TYPE_11__ {int BitWidth; int /*<<< orphan*/  SpaceId; int /*<<< orphan*/  Address; } ;
struct TYPE_9__ {int Length; scalar_t__ Pointer; } ;
struct TYPE_10__ {TYPE_1__ Buffer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  TYPE_3__ ACPI_GENERIC_ADDRESS ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_SYSTEM_IO ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_7__ AcpiGbl_FADT ; 
 int CPU_QUIRK_NO_THROTTLE ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_bus_alloc_gas (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int cpu_duty_offset ; 
 scalar_t__ cpu_duty_width ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,scalar_t__,int) ; 
 int thr_quirks ; 
 int /*<<< orphan*/  thr_rid ; 

__attribute__((used)) static int
acpi_throttle_evaluate(struct acpi_throttle_softc *sc)
{
	uint32_t duty_end;
	ACPI_BUFFER buf;
	ACPI_OBJECT obj;
	ACPI_GENERIC_ADDRESS gas;
	ACPI_STATUS status;

	/* Get throttling parameters from the FADT.  0 means not supported. */
	if (device_get_unit(sc->cpu_dev) == 0) {
		cpu_duty_offset = AcpiGbl_FADT.DutyOffset;
		cpu_duty_width = AcpiGbl_FADT.DutyWidth;
	}
	if (cpu_duty_width == 0 || (thr_quirks & CPU_QUIRK_NO_THROTTLE) != 0)
		return (ENXIO);

	/* Validate the duty offset/width. */
	duty_end = cpu_duty_offset + cpu_duty_width - 1;
	if (duty_end > 31) {
		device_printf(sc->cpu_dev,
		    "CLK_VAL field overflows P_CNT register\n");
		return (ENXIO);
	}
	if (cpu_duty_offset <= 4 && duty_end >= 4) {
		device_printf(sc->cpu_dev,
		    "CLK_VAL field overlaps THT_EN bit\n");
		return (ENXIO);
	}

	/*
	 * If not present, fall back to using the processor's P_BLK to find
	 * the P_CNT register.
	 *
	 * Note that some systems seem to duplicate the P_BLK pointer
	 * across multiple CPUs, so not getting the resource is not fatal.
	 */
	buf.Pointer = &obj;
	buf.Length = sizeof(obj);
	status = AcpiEvaluateObject(sc->cpu_handle, "_PTC", NULL, &buf);
	if (ACPI_SUCCESS(status)) {
		if (obj.Buffer.Length < sizeof(ACPI_GENERIC_ADDRESS) + 3) {
			device_printf(sc->cpu_dev, "_PTC buffer too small\n");
			return (ENXIO);
		}
		memcpy(&gas, obj.Buffer.Pointer + 3, sizeof(gas));
		acpi_bus_alloc_gas(sc->cpu_dev, &sc->cpu_p_type, &thr_rid,
		    &gas, &sc->cpu_p_cnt, 0);
		if (sc->cpu_p_cnt != NULL && bootverbose) {
			device_printf(sc->cpu_dev, "P_CNT from _PTC %#jx\n",
			    gas.Address);
		}
	}

	/* If _PTC not present or other failure, try the P_BLK. */
	if (sc->cpu_p_cnt == NULL) {
		/* 
		 * The spec says P_BLK must be 6 bytes long.  However, some
		 * systems use it to indicate a fractional set of features
		 * present so we take anything >= 4.
		 */
		if (sc->cpu_p_blk_len < 4)
			return (ENXIO);
		gas.Address = sc->cpu_p_blk;
		gas.SpaceId = ACPI_ADR_SPACE_SYSTEM_IO;
		gas.BitWidth = 32;
		acpi_bus_alloc_gas(sc->cpu_dev, &sc->cpu_p_type, &thr_rid,
		    &gas, &sc->cpu_p_cnt, 0);
		if (sc->cpu_p_cnt != NULL) {
			if (bootverbose)
				device_printf(sc->cpu_dev,
				    "P_CNT from P_BLK %#x\n", sc->cpu_p_blk);
		} else {
			device_printf(sc->cpu_dev, "failed to attach P_CNT\n");
			return (ENXIO);
		}
	}
	thr_rid++;

	return (0);
}