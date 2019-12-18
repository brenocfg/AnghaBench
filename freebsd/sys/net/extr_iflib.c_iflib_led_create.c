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
typedef  TYPE_1__* if_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  ifc_dev; int /*<<< orphan*/  ifc_led_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_led_func ; 
 int /*<<< orphan*/  led_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
iflib_led_create(if_ctx_t ctx)
{

	ctx->ifc_led_dev = led_create(iflib_led_func, ctx,
	    device_get_nameunit(ctx->ifc_dev));
}