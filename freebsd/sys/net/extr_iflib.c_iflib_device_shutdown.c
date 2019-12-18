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
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFDI_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int bus_generic_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 

int
iflib_device_shutdown(device_t dev)
{
	if_ctx_t ctx = device_get_softc(dev);

	CTX_LOCK(ctx);
	IFDI_SHUTDOWN(ctx);
	CTX_UNLOCK(ctx);

	return bus_generic_suspend(dev);
}