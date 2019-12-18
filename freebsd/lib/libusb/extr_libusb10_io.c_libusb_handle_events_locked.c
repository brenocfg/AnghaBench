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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/ * GET_CONTEXT (int /*<<< orphan*/ *) ; 
 int LIBUSB_ERROR_TIMEOUT ; 
 int libusb10_handle_events_sub (int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ libusb_event_handling_ok (int /*<<< orphan*/ *) ; 
 int libusb_wait_for_event (int /*<<< orphan*/ *,struct timeval*) ; 

int
libusb_handle_events_locked(libusb_context *ctx, struct timeval *tv)
{
	int err;

	ctx = GET_CONTEXT(ctx);

	if (libusb_event_handling_ok(ctx)) {
		err = libusb10_handle_events_sub(ctx, tv);
	} else {
		err = libusb_wait_for_event(ctx, tv);
		if (err != 0)
			err = LIBUSB_ERROR_TIMEOUT;
	}
	return (err);
}