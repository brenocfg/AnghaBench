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
struct vmbus_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_PCPU_GET (struct vmbus_softc const*,int /*<<< orphan*/ ,int) ; 
 struct vmbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpuid ; 

__attribute__((used)) static uint32_t
vmbus_get_vcpu_id_method(device_t bus, device_t dev, int cpu)
{
	const struct vmbus_softc *sc = device_get_softc(bus);

	return (VMBUS_PCPU_GET(sc, vcpuid, cpu));
}