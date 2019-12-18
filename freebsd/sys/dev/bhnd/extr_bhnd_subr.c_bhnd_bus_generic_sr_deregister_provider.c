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
struct bhnd_service_registry {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_service_t ;

/* Variables and functions */
 struct bhnd_service_registry* BHND_BUS_GET_SERVICE_REGISTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int bhnd_service_registry_remove (struct bhnd_service_registry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bhnd_bus_generic_sr_deregister_provider(device_t dev, device_t child,
    device_t provider, bhnd_service_t service)
{
	struct bhnd_service_registry *bsr;

	bsr = BHND_BUS_GET_SERVICE_REGISTRY(dev, child);

	KASSERT(bsr != NULL, ("NULL service registry"));

	return (bhnd_service_registry_remove(bsr, provider, service));
}