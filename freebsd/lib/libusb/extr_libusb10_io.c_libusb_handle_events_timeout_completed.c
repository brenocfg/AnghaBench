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
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GET_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int libusb_handle_events_locked (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  libusb_lock_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_unlock_events (int /*<<< orphan*/ *) ; 

int
libusb_handle_events_timeout_completed(libusb_context *ctx,
    struct timeval *tv, int *completed)
{
	int err = 0;

	ctx = GET_CONTEXT(ctx);

	DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "libusb_handle_events_timeout_completed enter");

	libusb_lock_events(ctx);

	while (1) {
		if (completed != NULL) {
			if (*completed != 0 || err != 0)
				break;
		}
		err = libusb_handle_events_locked(ctx, tv);
		if (completed == NULL)
			break;
	}

	libusb_unlock_events(ctx);

	DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "libusb_handle_events_timeout_completed exit");

	return (err);
}