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
 int libusb_handle_events_timeout_completed (int /*<<< orphan*/ *,struct timeval*,int /*<<< orphan*/ *) ; 

int
libusb_handle_events_timeout(libusb_context *ctx, struct timeval *tv)
{
	return (libusb_handle_events_timeout_completed(ctx, tv, NULL));
}