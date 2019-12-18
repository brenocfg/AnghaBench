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
struct ucom_super_softc {scalar_t__ sc_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ucom_mtx ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ucom_drain(struct ucom_super_softc *ssc)
{
	mtx_lock(&ucom_mtx);
	while (ssc->sc_refs > 0) {
		printf("ucom: Waiting for a TTY device to close.\n");
		usb_pause_mtx(&ucom_mtx, hz);
	}
	mtx_unlock(&ucom_mtx);
}