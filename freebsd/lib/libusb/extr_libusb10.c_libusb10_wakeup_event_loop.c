#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ctrl_pipe; } ;
typedef  TYPE_1__ libusb_context ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
libusb10_wakeup_event_loop(libusb_context *ctx)
{
	uint8_t dummy = 0;
	int err;

	err = write(ctx->ctrl_pipe[1], &dummy, sizeof(dummy));
	if (err < (int)sizeof(dummy)) {
		/* ignore error, if any */
		DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "Waking up event loop failed!");
	}
}