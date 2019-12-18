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
struct TYPE_4__ {int /*<<< orphan*/  oeminfo; int /*<<< orphan*/  type; int /*<<< orphan*/  serial; int /*<<< orphan*/  model; int /*<<< orphan*/  gra2; int /*<<< orphan*/  gra1; int /*<<< orphan*/  lcap; int /*<<< orphan*/  wcap; int /*<<< orphan*/  dvol; int /*<<< orphan*/  btech; int /*<<< orphan*/  lfcap; int /*<<< orphan*/  dcap; int /*<<< orphan*/  units; } ;
struct acpi_cmbat_softc {TYPE_1__ bif; } ;
typedef  void* device_t ;
struct TYPE_5__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_2__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_CMBAT_MAXSTRLEN ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_VPRINT (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_PkgInt32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_PkgStr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (void*) ; 
 int /*<<< orphan*/  acpi_get_handle (void*) ; 
 int /*<<< orphan*/  cmbat ; 
 struct acpi_cmbat_softc* device_get_softc (void*) ; 

__attribute__((used)) static void
acpi_cmbat_get_bif(void *arg)
{
    struct acpi_cmbat_softc *sc;
    ACPI_STATUS	as;
    ACPI_OBJECT	*res;
    ACPI_HANDLE	h;
    ACPI_BUFFER	bif_buffer;
    device_t dev;

    ACPI_SERIAL_ASSERT(cmbat);

    dev = arg;
    sc = device_get_softc(dev);
    h = acpi_get_handle(dev);
    bif_buffer.Pointer = NULL;
    bif_buffer.Length = ACPI_ALLOCATE_BUFFER;

    as = AcpiEvaluateObject(h, "_BIF", NULL, &bif_buffer);
    if (ACPI_FAILURE(as)) {
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "error fetching current battery info -- %s\n",
		    AcpiFormatException(as));
	goto end;
    }

    res = (ACPI_OBJECT *)bif_buffer.Pointer;
    if (!ACPI_PKG_VALID(res, 13)) {
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
		    "battery info corrupted\n");
	goto end;
    }

    if (acpi_PkgInt32(res, 0, &sc->bif.units) != 0)
	goto end;
    if (acpi_PkgInt32(res, 1, &sc->bif.dcap) != 0)
	goto end;
    if (acpi_PkgInt32(res, 2, &sc->bif.lfcap) != 0)
	goto end;
    if (acpi_PkgInt32(res, 3, &sc->bif.btech) != 0)
	goto end;
    if (acpi_PkgInt32(res, 4, &sc->bif.dvol) != 0)
	goto end;
    if (acpi_PkgInt32(res, 5, &sc->bif.wcap) != 0)
	goto end;
    if (acpi_PkgInt32(res, 6, &sc->bif.lcap) != 0)
	goto end;
    if (acpi_PkgInt32(res, 7, &sc->bif.gra1) != 0)
	goto end;
    if (acpi_PkgInt32(res, 8, &sc->bif.gra2) != 0)
	goto end;
    if (acpi_PkgStr(res,  9, sc->bif.model, ACPI_CMBAT_MAXSTRLEN) != 0)
	goto end;
    if (acpi_PkgStr(res, 10, sc->bif.serial, ACPI_CMBAT_MAXSTRLEN) != 0)
	goto end;
    if (acpi_PkgStr(res, 11, sc->bif.type, ACPI_CMBAT_MAXSTRLEN) != 0)
	goto end;
    if (acpi_PkgStr(res, 12, sc->bif.oeminfo, ACPI_CMBAT_MAXSTRLEN) != 0)
	goto end;

end:
    if (bif_buffer.Pointer != NULL)
	AcpiOsFree(bif_buffer.Pointer);
}