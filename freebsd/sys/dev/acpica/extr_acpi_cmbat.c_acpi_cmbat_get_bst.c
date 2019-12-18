#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; int rate; int cap; int volt; } ;
struct acpi_cmbat_softc {int flags; TYPE_1__ bst; int /*<<< orphan*/  bst_lastupdated; } ;
typedef  void* device_t ;
struct TYPE_5__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_2__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int ACPI_BATT_STAT_BST_MASK ; 
 int ACPI_BATT_STAT_CRITICAL ; 
 int ACPI_BATT_STAT_INVALID ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_VPRINT (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_PkgInt32 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  acpi_cmbat_info_expired (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_cmbat_info_updated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (void*) ; 
 int /*<<< orphan*/  acpi_get_handle (void*) ; 
 int /*<<< orphan*/  cmbat ; 
 struct acpi_cmbat_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 

__attribute__((used)) static void
acpi_cmbat_get_bst(void *arg)
{
    struct acpi_cmbat_softc *sc;
    ACPI_STATUS	as;
    ACPI_OBJECT	*res;
    ACPI_HANDLE	h;
    ACPI_BUFFER	bst_buffer;
    device_t dev;

    ACPI_SERIAL_ASSERT(cmbat);

    dev = arg;
    sc = device_get_softc(dev);
    h = acpi_get_handle(dev);
    bst_buffer.Pointer = NULL;
    bst_buffer.Length = ACPI_ALLOCATE_BUFFER;

    if (!acpi_cmbat_info_expired(&sc->bst_lastupdated))
	goto end;

    as = AcpiEvaluateObject(h, "_BST", NULL, &bst_buffer);
    if (ACPI_FAILURE(as)) {
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "error fetching current battery status -- %s\n",
		    AcpiFormatException(as));
	goto end;
    }

    res = (ACPI_OBJECT *)bst_buffer.Pointer;
    if (!ACPI_PKG_VALID(res, 4)) {
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "battery status corrupted\n");
	goto end;
    }

    if (acpi_PkgInt32(res, 0, &sc->bst.state) != 0)
	goto end;
    if (acpi_PkgInt32(res, 1, &sc->bst.rate) != 0)
	goto end;
    if (acpi_PkgInt32(res, 2, &sc->bst.cap) != 0)
	goto end;
    if (acpi_PkgInt32(res, 3, &sc->bst.volt) != 0)
	goto end;
    acpi_cmbat_info_updated(&sc->bst_lastupdated);

    /* Clear out undefined/extended bits that might be set by hardware. */
    sc->bst.state &= ACPI_BATT_STAT_BST_MASK;
    if ((sc->bst.state & ACPI_BATT_STAT_INVALID) == ACPI_BATT_STAT_INVALID)
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
	    "battery reports simultaneous charging and discharging\n");

    /* XXX If all batteries are critical, perhaps we should suspend. */
    if (sc->bst.state & ACPI_BATT_STAT_CRITICAL) {
    	if ((sc->flags & ACPI_BATT_STAT_CRITICAL) == 0) {
	    sc->flags |= ACPI_BATT_STAT_CRITICAL;
	    device_printf(dev, "critically low charge!\n");
	}
    } else
	sc->flags &= ~ACPI_BATT_STAT_CRITICAL;

end:
    if (bst_buffer.Pointer != NULL)
	AcpiOsFree(bst_buffer.Pointer);
}