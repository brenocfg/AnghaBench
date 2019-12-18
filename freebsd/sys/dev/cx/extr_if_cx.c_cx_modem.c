#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dcd_timeout_handle; } ;
typedef  TYPE_1__ drv_t ;
struct TYPE_6__ {scalar_t__ mode; TYPE_1__* sys; } ;
typedef  TYPE_2__ cx_chan_t ;

/* Variables and functions */
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cx_carrier ; 
 int hz ; 

__attribute__((used)) static void cx_modem (cx_chan_t *c)
{
	drv_t *d = c->sys;

	if (!d || c->mode != M_ASYNC)
		return;
	/* Handle carrier detect/loss. */
	/* Carrier changed - delay processing DCD for a while
	 * to give both sides some time to initialize. */
	callout_reset (&d->dcd_timeout_handle, hz/2, cx_carrier, d);
}