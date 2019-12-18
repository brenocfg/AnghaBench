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
typedef  void* uint32_t ;
struct auth_xfer {int notify_received; int notify_has_serial; void* notify_serial; } ;

/* Variables and functions */
 scalar_t__ compare_serial (void*,void*) ; 

__attribute__((used)) static void
xfr_note_notify_serial(struct auth_xfer* xfr, int has_serial, uint32_t serial)
{
	if(xfr->notify_received && xfr->notify_has_serial && has_serial) {
		/* see if this serial is newer */
		if(compare_serial(xfr->notify_serial, serial) < 0)
			xfr->notify_serial = serial;
	} else if(xfr->notify_received && xfr->notify_has_serial &&
		!has_serial) {
		/* remove serial, we have notify without serial */
		xfr->notify_has_serial = 0;
		xfr->notify_serial = 0;
	} else if(xfr->notify_received && !xfr->notify_has_serial) {
		/* we already have notify without serial, keep it
		 * that way; no serial check when current operation
		 * is done */
	} else {
		xfr->notify_received = 1;
		xfr->notify_has_serial = has_serial;
		xfr->notify_serial = serial;
	}
}