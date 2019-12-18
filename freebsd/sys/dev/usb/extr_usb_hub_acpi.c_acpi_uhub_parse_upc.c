#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct sysctl_oid_list {int dummy; } ;
struct acpi_uhub_softc {struct acpi_uhub_port* port; } ;
struct acpi_uhub_port {scalar_t__ upc; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ UINT64 ;
struct TYPE_3__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_UPC_CONNECTABLE ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_U32 (int /*<<< orphan*/ ,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SYSCTL_NULL_U32_PTR ; 
 int /*<<< orphan*/  acpi_PkgInt (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_uhub_upc_type (scalar_t__) ; 
 struct acpi_uhub_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_debug ; 

__attribute__((used)) static int
acpi_uhub_parse_upc(device_t dev, unsigned int p, ACPI_HANDLE ah, struct sysctl_oid_list *poid)
{
	ACPI_BUFFER buf;
	struct acpi_uhub_softc *sc = device_get_softc(dev);
	struct acpi_uhub_port *port = &sc->port[p - 1];

	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;

	if (AcpiEvaluateObject(ah, "_UPC", NULL, &buf) == AE_OK) {
		ACPI_OBJECT *obj = buf.Pointer;
		UINT64 porttypenum, conn;
		uint8_t *connectable;

		acpi_PkgInt(obj, 0, &conn);
		acpi_PkgInt(obj, 1, &porttypenum);
		connectable = conn ? "" : "non";

		port->upc = porttypenum;
		port->upc |= (conn) ? (ACPI_UPC_CONNECTABLE) : 0;

		if (usb_debug)
			device_printf(dev, "Port %u %sconnectable %s\n",
			    p, connectable,
			    acpi_uhub_upc_type(porttypenum));

		SYSCTL_ADD_U32(
		    device_get_sysctl_ctx(dev),
		    poid, OID_AUTO,
		    "upc",
		    CTLFLAG_RD | CTLFLAG_MPSAFE,
		    SYSCTL_NULL_U32_PTR, port->upc,
		    "UPC value. MSB is visible flag");
	}
	AcpiOsFree(buf.Pointer);

	return (0);
}