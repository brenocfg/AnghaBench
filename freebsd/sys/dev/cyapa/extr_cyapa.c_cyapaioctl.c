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
typedef  int u_long ;
struct thread {int dummy; } ;
struct TYPE_3__ {int level; int /*<<< orphan*/  packetsize; void* protocol; scalar_t__ resolution; } ;
struct TYPE_4__ {int /*<<< orphan*/  model; } ;
struct cyapa_softc {int zenabled; TYPE_1__ mode; TYPE_2__ hw; } ;
struct cdev {struct cyapa_softc* si_drv1; } ;
typedef  TYPE_1__ mousemode_t ;
typedef  TYPE_2__ mousehw_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
#define  MOUSE_GETHWINFO 131 
#define  MOUSE_GETLEVEL 130 
#define  MOUSE_GETMODE 129 
 int /*<<< orphan*/  MOUSE_MODEL_GENERIC ; 
 void* MOUSE_PROTO_PS2 ; 
 int /*<<< orphan*/  MOUSE_PS2_PACKETSIZE ; 
 scalar_t__ MOUSE_RES_LOW ; 
#define  MOUSE_SETLEVEL 128 
 int /*<<< orphan*/  cyapa_lock (struct cyapa_softc*) ; 
 int /*<<< orphan*/  cyapa_unlock (struct cyapa_softc*) ; 

__attribute__((used)) static int
cyapaioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag, struct thread *td)
{
	struct cyapa_softc *sc;
	int error;

	sc = dev->si_drv1;
	error = 0;

	cyapa_lock(sc);
	switch (cmd) {
	case MOUSE_GETHWINFO:
		*(mousehw_t *)data = sc->hw;
		if (sc->mode.level == 0)
			((mousehw_t *)data)->model = MOUSE_MODEL_GENERIC;
		break;

	case MOUSE_GETMODE:
		*(mousemode_t *)data = sc->mode;
		((mousemode_t *)data)->resolution =
		    MOUSE_RES_LOW - sc->mode.resolution;
		switch (sc->mode.level) {
		case 0:
			((mousemode_t *)data)->protocol = MOUSE_PROTO_PS2;
			((mousemode_t *)data)->packetsize =
			    MOUSE_PS2_PACKETSIZE;
			break;
		case 2:
			((mousemode_t *)data)->protocol = MOUSE_PROTO_PS2;
			((mousemode_t *)data)->packetsize =
			    MOUSE_PS2_PACKETSIZE + 1;
			break;
		}
		break;

	case MOUSE_GETLEVEL:
		*(int *)data = sc->mode.level;
		break;

	case MOUSE_SETLEVEL:
		if ((*(int *)data < 0) &&
		    (*(int *)data > 2)) {
			error = EINVAL;
			break;
		}
		sc->mode.level = *(int *)data ? 2 : 0;
		sc->zenabled = sc->mode.level ? 1 : 0;
		break;

	default:
		error = ENOTTY;
		break;
	}
	cyapa_unlock(sc);

	return (error);
}