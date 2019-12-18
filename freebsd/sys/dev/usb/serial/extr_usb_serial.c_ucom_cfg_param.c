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
struct usb_proc_msg {int dummy; } ;
struct ucom_softc {int sc_flag; int /*<<< orphan*/  sc_mtx; TYPE_1__* sc_callback; } ;
struct ucom_param_task {int /*<<< orphan*/  termios_copy; struct ucom_softc* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucom_cfg_param ) (struct ucom_softc*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int UCOM_FLAG_LL_READY ; 
 int hz ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ucom_cfg_param(struct usb_proc_msg *_task)
{
	struct ucom_param_task *task = 
	    (struct ucom_param_task *)_task;
	struct ucom_softc *sc = task->sc;

	if (!(sc->sc_flag & UCOM_FLAG_LL_READY)) {
		return;
	}
	if (sc->sc_callback->ucom_cfg_param == NULL) {
		return;
	}

	(sc->sc_callback->ucom_cfg_param) (sc, &task->termios_copy);

	/* wait a little */
	usb_pause_mtx(sc->sc_mtx, hz / 10);
}