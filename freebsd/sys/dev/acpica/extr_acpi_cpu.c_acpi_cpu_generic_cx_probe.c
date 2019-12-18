#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpi_cx {int trans_lat; int res_rid; int /*<<< orphan*/  type; int /*<<< orphan*/ * p_lvlx; int /*<<< orphan*/  res_type; } ;
struct acpi_cpu_softc {int cpu_prev_sleep; int cpu_p_blk_len; scalar_t__ cpu_cx_count; int /*<<< orphan*/  cpu_dev; scalar_t__ cpu_p_blk; scalar_t__ cpu_non_c3; scalar_t__ cpu_non_c2; struct acpi_cx* cpu_cx_states; } ;
struct TYPE_5__ {int C2Latency; int C3Latency; } ;
struct TYPE_4__ {int BitWidth; scalar_t__ Address; int /*<<< orphan*/  SpaceId; } ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_SYSTEM_IO ; 
 int /*<<< orphan*/  ACPI_STATE_C1 ; 
 int /*<<< orphan*/  ACPI_STATE_C2 ; 
 int /*<<< orphan*/  ACPI_STATE_C3 ; 
 TYPE_3__ AcpiGbl_FADT ; 
 int CPU_QUIRK_NO_C3 ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  acpi_bus_alloc_gas (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int cpu_quirks ; 

__attribute__((used)) static void
acpi_cpu_generic_cx_probe(struct acpi_cpu_softc *sc)
{
    ACPI_GENERIC_ADDRESS	 gas;
    struct acpi_cx		*cx_ptr;

    sc->cpu_cx_count = 0;
    cx_ptr = sc->cpu_cx_states;

    /* Use initial sleep value of 1 sec. to start with lowest idle state. */
    sc->cpu_prev_sleep = 1000000;

    /* C1 has been required since just after ACPI 1.0 */
    cx_ptr->type = ACPI_STATE_C1;
    cx_ptr->trans_lat = 0;
    cx_ptr++;
    sc->cpu_non_c2 = sc->cpu_cx_count;
    sc->cpu_non_c3 = sc->cpu_cx_count;
    sc->cpu_cx_count++;

    /* 
     * The spec says P_BLK must be 6 bytes long.  However, some systems
     * use it to indicate a fractional set of features present so we
     * take 5 as C2.  Some may also have a value of 7 to indicate
     * another C3 but most use _CST for this (as required) and having
     * "only" C1-C3 is not a hardship.
     */
    if (sc->cpu_p_blk_len < 5)
	return; 

    /* Validate and allocate resources for C2 (P_LVL2). */
    gas.SpaceId = ACPI_ADR_SPACE_SYSTEM_IO;
    gas.BitWidth = 8;
    if (AcpiGbl_FADT.C2Latency <= 100) {
	gas.Address = sc->cpu_p_blk + 4;
	cx_ptr->res_rid = 0;
	acpi_bus_alloc_gas(sc->cpu_dev, &cx_ptr->res_type, &cx_ptr->res_rid,
	    &gas, &cx_ptr->p_lvlx, RF_SHAREABLE);
	if (cx_ptr->p_lvlx != NULL) {
	    cx_ptr->type = ACPI_STATE_C2;
	    cx_ptr->trans_lat = AcpiGbl_FADT.C2Latency;
	    cx_ptr++;
	    sc->cpu_non_c3 = sc->cpu_cx_count;
	    sc->cpu_cx_count++;
	}
    }
    if (sc->cpu_p_blk_len < 6)
	return;

    /* Validate and allocate resources for C3 (P_LVL3). */
    if (AcpiGbl_FADT.C3Latency <= 1000 && !(cpu_quirks & CPU_QUIRK_NO_C3)) {
	gas.Address = sc->cpu_p_blk + 5;
	cx_ptr->res_rid = 1;
	acpi_bus_alloc_gas(sc->cpu_dev, &cx_ptr->res_type, &cx_ptr->res_rid,
	    &gas, &cx_ptr->p_lvlx, RF_SHAREABLE);
	if (cx_ptr->p_lvlx != NULL) {
	    cx_ptr->type = ACPI_STATE_C3;
	    cx_ptr->trans_lat = AcpiGbl_FADT.C3Latency;
	    cx_ptr++;
	    sc->cpu_cx_count++;
	}
    }
}