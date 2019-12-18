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
struct TYPE_4__ {int timeout; int /*<<< orphan*/  timeout_handle; int /*<<< orphan*/ * bd; } ;
typedef  TYPE_1__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CT_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  ct_watchdog (TYPE_1__*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void ct_watchdog_timer (void *arg)
{
	drv_t *d = arg;
	bdrv_t *bd = d->bd;

	CT_LOCK (bd);
	if (d->timeout == 1)
		ct_watchdog (d);
	if (d->timeout)
		d->timeout--;
	callout_reset (&d->timeout_handle, hz, ct_watchdog_timer, d);
	CT_UNLOCK (bd);
}