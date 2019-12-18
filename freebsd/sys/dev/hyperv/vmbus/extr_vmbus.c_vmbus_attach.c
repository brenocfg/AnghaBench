#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {TYPE_1__* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct TYPE_5__ {int vmbus_idtvec; TYPE_4__ vmbus_intrhook; int /*<<< orphan*/  vmbus_event_proc; int /*<<< orphan*/  vmbus_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  config_intrhook_establish (TYPE_4__*) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_doattach (TYPE_1__*) ; 
 int /*<<< orphan*/  vmbus_event_proc_dummy ; 
 int /*<<< orphan*/  vmbus_intrhook ; 
 TYPE_1__* vmbus_sc ; 

__attribute__((used)) static int
vmbus_attach(device_t dev)
{
	vmbus_sc = device_get_softc(dev);
	vmbus_sc->vmbus_dev = dev;
	vmbus_sc->vmbus_idtvec = -1;

	/*
	 * Event processing logic will be configured:
	 * - After the vmbus protocol version negotiation.
	 * - Before we request channel offers.
	 */
	vmbus_sc->vmbus_event_proc = vmbus_event_proc_dummy;

#ifdef EARLY_AP_STARTUP
	/*
	 * Defer the real attach until the pause(9) works as expected.
	 */
	vmbus_sc->vmbus_intrhook.ich_func = vmbus_intrhook;
	vmbus_sc->vmbus_intrhook.ich_arg = vmbus_sc;
	config_intrhook_establish(&vmbus_sc->vmbus_intrhook);
#else	/* !EARLY_AP_STARTUP */
	/* 
	 * If the system has already booted and thread
	 * scheduling is possible indicated by the global
	 * cold set to zero, we just call the driver
	 * initialization directly.
	 */
	if (!cold)
		vmbus_doattach(vmbus_sc);
#endif	/* EARLY_AP_STARTUP */

	return (0);
}