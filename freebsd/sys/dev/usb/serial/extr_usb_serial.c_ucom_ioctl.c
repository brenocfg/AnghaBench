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
typedef  int u_long ;
struct ucom_softc {int sc_flag; int /*<<< orphan*/  sc_pps; TYPE_1__* sc_callback; } ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int (* ucom_ioctl ) (struct ucom_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int EIO ; 
 int ENOIOCTL ; 
 int /*<<< orphan*/  MA_OWNED ; 
#define  TIOCCBRK 131 
#define  TIOCCRING 130 
#define  TIOCSBRK 129 
#define  TIOCSRING 128 
 int UCOM_FLAG_HL_READY ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int pps_ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct ucom_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 struct ucom_softc* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  ucom_break (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  ucom_ring (struct ucom_softc*,int) ; 

__attribute__((used)) static int
ucom_ioctl(struct tty *tp, u_long cmd, caddr_t data, struct thread *td)
{
	struct ucom_softc *sc = tty_softc(tp);
	int error;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return (EIO);
	}
	DPRINTF("cmd = 0x%08lx\n", cmd);

	switch (cmd) {
#if 0
	case TIOCSRING:
		ucom_ring(sc, 1);
		error = 0;
		break;
	case TIOCCRING:
		ucom_ring(sc, 0);
		error = 0;
		break;
#endif
	case TIOCSBRK:
		ucom_break(sc, 1);
		error = 0;
		break;
	case TIOCCBRK:
		ucom_break(sc, 0);
		error = 0;
		break;
	default:
		if (sc->sc_callback->ucom_ioctl) {
			error = (sc->sc_callback->ucom_ioctl)
			    (sc, cmd, data, 0, td);
		} else {
			error = ENOIOCTL;
		}
		if (error == ENOIOCTL)
			error = pps_ioctl(cmd, data, &sc->sc_pps);
		break;
	}
	return (error);
}