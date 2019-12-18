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
struct TYPE_5__ {scalar_t__ debug_fixed; int debug; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 

void
libusb_set_debug(libusb_context *ctx, int level)
{
	ctx = GET_CONTEXT(ctx);
	/* debug_fixed is set when the environment overrides libusb_set_debug */
	if (ctx && ctx->debug_fixed == 0)
		ctx->debug = level;
}