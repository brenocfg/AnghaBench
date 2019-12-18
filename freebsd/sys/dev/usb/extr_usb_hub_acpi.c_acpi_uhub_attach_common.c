#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hub {int nports; } ;
struct TYPE_4__ {TYPE_1__* sc_udev; } ;
struct acpi_uhub_softc {int nports; int /*<<< orphan*/  ah; int /*<<< orphan*/  port; TYPE_2__ usc; } ;
struct acpi_uhub_port {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {struct usb_hub* hub; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  acpi_usb_hub_port_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_uhub_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_uhub_attach_common(device_t dev)
{
	struct usb_hub *uh;
	struct acpi_uhub_softc *sc = device_get_softc(dev);
	ACPI_STATUS status;
	int ret = ENXIO;

	uh = sc->usc.sc_udev->hub;
	sc->nports = uh->nports;
	sc->port = malloc(sizeof(struct acpi_uhub_port) * uh->nports,
	    M_USBDEV, M_WAITOK | M_ZERO);
	status = acpi_usb_hub_port_probe(dev, sc->ah);

	if (ACPI_SUCCESS(status)){
		ret = 0;
	} 

	return (ret);
}