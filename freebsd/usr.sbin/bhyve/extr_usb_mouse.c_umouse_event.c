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
typedef  int uint8_t ;
struct TYPE_3__ {int buttons; int z; int x; int y; } ;
struct umouse_softc {int newdata; int /*<<< orphan*/  ev_mtx; TYPE_2__* hci; int /*<<< orphan*/  mtx; TYPE_1__ um_report; } ;
struct bhyvegc_image {int width; int height; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hci_intr ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int MOUSE_MAX_X ; 
 int MOUSE_MAX_Y ; 
 int UE_DIR_IN ; 
 int UMOUSE_INTR_ENDPT ; 
 struct bhyvegc_image* console_get_image () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void
umouse_event(uint8_t button, int x, int y, void *arg)
{
	struct umouse_softc *sc;
	struct bhyvegc_image *gc;

	gc = console_get_image();
	if (gc == NULL) {
		/* not ready */
		return;
	}

	sc = arg;

	pthread_mutex_lock(&sc->mtx);

	sc->um_report.buttons = 0;
	sc->um_report.z = 0;

	if (button & 0x01)
		sc->um_report.buttons |= 0x01;	/* left */
	if (button & 0x02)
		sc->um_report.buttons |= 0x04;	/* middle */
	if (button & 0x04)
		sc->um_report.buttons |= 0x02;	/* right */
	if (button & 0x8)
		sc->um_report.z = 1;
	if (button & 0x10)
		sc->um_report.z = -1;

	/* scale coords to mouse resolution */
	sc->um_report.x = MOUSE_MAX_X * x / gc->width;
	sc->um_report.y = MOUSE_MAX_Y * y / gc->height;
	sc->newdata = 1;
	pthread_mutex_unlock(&sc->mtx);

	pthread_mutex_lock(&sc->ev_mtx);
	sc->hci->hci_intr(sc->hci, UE_DIR_IN | UMOUSE_INTR_ENDPT);
	pthread_mutex_unlock(&sc->ev_mtx);
}