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
typedef  int uint32_t ;
struct umodem_softc {int sc_cm_over_data; } ;
struct ucom_softc {struct umodem_softc* sc_parent; } ;
struct thread {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int ENOIOCTL ; 
#define  USB_GET_CM_OVER_DATA 129 
#define  USB_SET_CM_OVER_DATA 128 

__attribute__((used)) static int
umodem_ioctl(struct ucom_softc *ucom, uint32_t cmd, caddr_t data,
    int flag, struct thread *td)
{
	struct umodem_softc *sc = ucom->sc_parent;
	int error = 0;

	DPRINTF("cmd=0x%08x\n", cmd);

	switch (cmd) {
	case USB_GET_CM_OVER_DATA:
		*(int *)data = sc->sc_cm_over_data;
		break;

	case USB_SET_CM_OVER_DATA:
		if (*(int *)data != sc->sc_cm_over_data) {
			/* XXX change it */
		}
		break;

	default:
		DPRINTF("unknown\n");
		error = ENOIOCTL;
		break;
	}

	return (error);
}