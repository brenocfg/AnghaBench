#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * libusb_hotplug_callback_handle ;
struct TYPE_7__ {int /*<<< orphan*/  hotplug_cbh; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  HOTPLUG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  HOTPLUG_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void libusb_hotplug_deregister_callback(libusb_context *ctx,
    libusb_hotplug_callback_handle handle)
{
  	ctx = GET_CONTEXT(ctx);

	if (ctx == NULL || handle == NULL)
		return;

	HOTPLUG_LOCK(ctx);
	TAILQ_REMOVE(&ctx->hotplug_cbh, handle, entry);
	HOTPLUG_UNLOCK(ctx);

	free(handle);
}