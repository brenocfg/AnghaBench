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
struct thread {int dummy; } ;
struct cdev {struct acpi_wmi_softc* si_drv1; } ;
struct acpi_wmi_softc {scalar_t__ wmistat_open_pid; int wmistat_bufptr; int /*<<< orphan*/  wmistat_sbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int EBADF ; 
 int /*<<< orphan*/  acpi_wmi ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_wmi_wmistat_close(struct cdev* dev, int flags, int mode,
    struct thread *td)
{
	struct acpi_wmi_softc *sc;
	int ret;

	if (dev == NULL || dev->si_drv1 == NULL)
		return (EBADF);
	sc = dev->si_drv1;

	ACPI_SERIAL_BEGIN(acpi_wmi);
	if (sc->wmistat_open_pid == 0) {
		ret = EBADF;
	}
	else {
		if (sc->wmistat_bufptr != -1) {
			sbuf_delete(&sc->wmistat_sbuf);
			sc->wmistat_bufptr = -1;
		}
		sc->wmistat_open_pid = 0;
		ret = 0;
	}
	ACPI_SERIAL_END(acpi_wmi);

	return (ret);
}