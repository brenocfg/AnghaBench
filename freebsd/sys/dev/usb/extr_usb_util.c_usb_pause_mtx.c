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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

void
usb_pause_mtx(struct mtx *mtx, int timo)
{
	if (mtx != NULL)
		mtx_unlock(mtx);

	/*
	 * Add one tick to the timeout so that we don't return too
	 * early! Note that pause() will assert that the passed
	 * timeout is positive and non-zero!
	 */
	pause("USBWAIT", timo + 1);

	if (mtx != NULL)
		mtx_lock(mtx);
}