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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmbus_softc {int /*<<< orphan*/  vmbus_version; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct vmbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
vmbus_get_version_method(device_t bus, device_t dev)
{
	struct vmbus_softc *sc = device_get_softc(bus);

	return sc->vmbus_version;
}