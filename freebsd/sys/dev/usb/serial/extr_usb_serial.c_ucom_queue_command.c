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
typedef  int /*<<< orphan*/  usb_proc_callback_t ;
struct usb_proc_msg {int dummy; } ;
struct ucom_super_softc {int /*<<< orphan*/  sc_tq; } ;
struct ucom_softc {TYPE_1__* sc_last_start_xfer; struct ucom_super_softc* sc_super; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pm_callback; } ;
struct termios {int dummy; } ;
struct ucom_param_task {TYPE_1__ hdr; struct termios termios_copy; struct ucom_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucom_cfg_close ; 
 int /*<<< orphan*/ * ucom_cfg_start_transfers ; 
 scalar_t__ usb_proc_is_gone (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_proc_msignal (int /*<<< orphan*/ *,struct usb_proc_msg*,struct usb_proc_msg*) ; 
 int /*<<< orphan*/  usb_proc_mwait (int /*<<< orphan*/ *,struct usb_proc_msg*,struct usb_proc_msg*) ; 

__attribute__((used)) static void
ucom_queue_command(struct ucom_softc *sc,
    usb_proc_callback_t *fn, struct termios *pt,
    struct usb_proc_msg *t0, struct usb_proc_msg *t1)
{
	struct ucom_super_softc *ssc = sc->sc_super;
	struct ucom_param_task *task;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (usb_proc_is_gone(&ssc->sc_tq)) {
		DPRINTF("proc is gone\n");
		return;         /* nothing to do */
	}
	/* 
	 * NOTE: The task cannot get executed before we drop the
	 * "sc_mtx" mutex. It is safe to update fields in the message
	 * structure after that the message got queued.
	 */
	task = (struct ucom_param_task *)
	  usb_proc_msignal(&ssc->sc_tq, t0, t1);

	/* Setup callback and softc pointers */
	task->hdr.pm_callback = fn;
	task->sc = sc;

	/* 
	 * Make a copy of the termios. This field is only present if
	 * the "pt" field is not NULL.
	 */
	if (pt != NULL)
		task->termios_copy = *pt;

	/*
	 * Closing the device should be synchronous.
	 */
	if (fn == ucom_cfg_close)
		usb_proc_mwait(&ssc->sc_tq, t0, t1);

	/*
	 * In case of multiple configure requests,
	 * keep track of the last one!
	 */
	if (fn == ucom_cfg_start_transfers)
		sc->sc_last_start_xfer = &task->hdr;
}