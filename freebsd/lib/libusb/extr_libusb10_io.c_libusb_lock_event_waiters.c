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
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GET_CONTEXT (int /*<<< orphan*/ *) ; 

void
libusb_lock_event_waiters(libusb_context *ctx)
{
	ctx = GET_CONTEXT(ctx);
	CTX_LOCK(ctx);
}