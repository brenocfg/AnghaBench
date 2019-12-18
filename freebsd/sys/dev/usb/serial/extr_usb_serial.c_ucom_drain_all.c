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

/* Variables and functions */
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ ucom_close_refs ; 
 int /*<<< orphan*/  ucom_mtx ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ucom_drain_all(void *arg)
{
	mtx_lock(&ucom_mtx);
	while (ucom_close_refs > 0) {
		printf("ucom: Waiting for all detached TTY "
		    "devices to have open fds closed.\n");
		usb_pause_mtx(&ucom_mtx, hz);
	}
	mtx_unlock(&ucom_mtx);
}