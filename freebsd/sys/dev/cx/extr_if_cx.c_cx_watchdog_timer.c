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
struct TYPE_6__ {int timeout; int /*<<< orphan*/  timeout_handle; TYPE_1__* board; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_5__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_2__*) ; 
 int /*<<< orphan*/  cx_watchdog (TYPE_2__*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void cx_watchdog_timer (void *arg)
{
	drv_t *d = arg;
	bdrv_t *bd = d->board->sys;

	CX_LOCK (bd);
	if (d->timeout == 1)
		cx_watchdog (d);
	if (d->timeout)
		d->timeout--;
	callout_reset (&d->timeout_handle, hz, cx_watchdog_timer, d);
	CX_UNLOCK (bd);
}