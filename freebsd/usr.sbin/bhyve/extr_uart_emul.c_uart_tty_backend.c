#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rfd; int wfd; int opened; } ;
struct uart_softc {TYPE_1__ tty; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  cap_ioctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_EVENT ; 
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TIOCGETA ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TIOCSETA ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int caph_ioctls_limit (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isatty (int) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ *) ; 
 int open (char const*,int) ; 

__attribute__((used)) static int
uart_tty_backend(struct uart_softc *sc, const char *opts)
{
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights;
	cap_ioctl_t cmds[] = { TIOCGETA, TIOCSETA, TIOCGWINSZ };
#endif
	int fd;

	fd = open(opts, O_RDWR | O_NONBLOCK);
	if (fd < 0)
		return (-1);

	if (!isatty(fd)) {
		close(fd);
		return (-1);
	}

	sc->tty.rfd = sc->tty.wfd = fd;
	sc->tty.opened = true;

#ifndef WITHOUT_CAPSICUM
	cap_rights_init(&rights, CAP_EVENT, CAP_IOCTL, CAP_READ, CAP_WRITE);
	if (caph_rights_limit(fd, &rights) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
	if (caph_ioctls_limit(fd, cmds, nitems(cmds)) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif

	return (0);
}