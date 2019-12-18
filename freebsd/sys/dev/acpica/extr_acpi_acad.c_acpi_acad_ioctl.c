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
typedef  int u_long ;
struct acpi_acad_softc {int status; } ;
typedef  scalar_t__ device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  ACPIIO_ACAD_GET_STATUS 128 
 int /*<<< orphan*/  acpi_acad_get_status (scalar_t__) ; 
 struct acpi_acad_softc* device_get_softc (scalar_t__) ; 

__attribute__((used)) static int
acpi_acad_ioctl(u_long cmd, caddr_t addr, void *arg)
{
    struct acpi_acad_softc *sc;
    device_t dev;

    dev = (device_t)arg;
    sc = device_get_softc(dev);

    /*
     * No security check required: information retrieval only.  If
     * new functions are added here, a check might be required.
     */
    switch (cmd) {
    case ACPIIO_ACAD_GET_STATUS:
	acpi_acad_get_status(dev);
	*(int *)addr = sc->status;
	break;
    default:
	break;
    }

    return (0);
}