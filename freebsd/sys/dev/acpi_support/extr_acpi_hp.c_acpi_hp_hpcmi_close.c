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
struct cdev {struct acpi_hp_softc* si_drv1; } ;
struct acpi_hp_softc {scalar_t__ hpcmi_open_pid; int hpcmi_bufptr; int /*<<< orphan*/  hpcmi_sbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int EBADF ; 
 int /*<<< orphan*/  hp ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_hp_hpcmi_close(struct cdev* dev, int flags, int mode, struct thread *td)
{
	struct acpi_hp_softc	*sc;
	int			ret;

	if (dev == NULL || dev->si_drv1 == NULL)
		return (EBADF);
	sc = dev->si_drv1;

	ACPI_SERIAL_BEGIN(hp);
	if (sc->hpcmi_open_pid == 0) {
		ret = EBADF;
	}
	else {
		if (sc->hpcmi_bufptr != -1) {
			sbuf_delete(&sc->hpcmi_sbuf);
			sc->hpcmi_bufptr = -1;
		}
		sc->hpcmi_open_pid = 0;
		ret = 0;
	}
	ACPI_SERIAL_END(hp);

	return (ret);
}