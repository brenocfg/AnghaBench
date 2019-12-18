#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  size_t uint64_t ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct acpi_uhub_softc {TYPE_2__* port; scalar_t__ nports; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_6__ {int upc; int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {int Valid; size_t Address; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_DEVICE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_ADR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetObjectInfo (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_1__*) ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  acpi_uhub_parse_pld (void*,size_t,int /*<<< orphan*/ ,struct sysctl_oid_list*) ; 
 int /*<<< orphan*/  acpi_uhub_parse_upc (void*,size_t,int /*<<< orphan*/ ,struct sysctl_oid_list*) ; 
 int /*<<< orphan*/  acpi_uhub_port_sysctl ; 
 struct acpi_uhub_softc* device_get_softc (void*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (void*) ; 
 struct sysctl_oid* device_get_sysctl_tree (void*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
acpi_usb_hub_port_probe_cb(ACPI_HANDLE ah, UINT32 lv, void *ctx, void **rv)
{
	ACPI_DEVICE_INFO *devinfo;
	device_t dev = ctx;
	struct acpi_uhub_softc *sc = device_get_softc(dev);
	UINT32 ret;

	ret = AcpiGetObjectInfo(ah, &devinfo);
	if (ACPI_SUCCESS(ret)) {
		if ((devinfo->Valid & ACPI_VALID_ADR) &&
		    (devinfo->Address > 0) &&
		    (devinfo->Address <= (uint64_t)sc->nports)) {
			char buf[] = "portXXX";
			struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
			struct sysctl_oid *oid;
			struct sysctl_oid_list *tree;
			
			snprintf(buf, sizeof(buf), "port%ju",
			    (uintmax_t)devinfo->Address);
			oid = SYSCTL_ADD_NODE(ctx,
					      SYSCTL_CHILDREN(
						      device_get_sysctl_tree(dev)),
					      OID_AUTO, buf, CTLFLAG_RD,
					      NULL, "port nodes");
			tree = SYSCTL_CHILDREN(oid);
			sc->port[devinfo->Address - 1].handle = ah;
			sc->port[devinfo->Address - 1].upc = 0xffffffff;
			acpi_uhub_parse_upc(dev, devinfo->Address, ah, tree);
			acpi_uhub_parse_pld(dev, devinfo->Address, ah, tree);
			SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
					tree, OID_AUTO, "info",
					CTLTYPE_STRING | CTLFLAG_RD,
					&sc->port[devinfo->Address - 1], 0,
					acpi_uhub_port_sysctl,
					"A", "Port information");
		}
		AcpiOsFree(devinfo);
	}
	return (AE_OK);
}