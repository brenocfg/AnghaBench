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
struct TYPE_5__ {scalar_t__ ctx_handler; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 
 scalar_t__ NO_THREAD ; 

int
libusb_event_handler_active(libusb_context *ctx)
{
	ctx = GET_CONTEXT(ctx);
	return (ctx->ctx_handler != NO_THREAD);
}