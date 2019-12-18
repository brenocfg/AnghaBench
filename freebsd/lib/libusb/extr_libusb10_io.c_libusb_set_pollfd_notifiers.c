#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libusb_pollfd_removed_cb ;
typedef  int /*<<< orphan*/  libusb_pollfd_added_cb ;
struct TYPE_5__ {void* fd_cb_user_data; int /*<<< orphan*/  fd_removed_cb; int /*<<< orphan*/  fd_added_cb; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 

void
libusb_set_pollfd_notifiers(libusb_context *ctx,
    libusb_pollfd_added_cb added_cb, libusb_pollfd_removed_cb removed_cb,
    void *user_data)
{
	ctx = GET_CONTEXT(ctx);

	ctx->fd_added_cb = added_cb;
	ctx->fd_removed_cb = removed_cb;
	ctx->fd_cb_user_data = user_data;
}