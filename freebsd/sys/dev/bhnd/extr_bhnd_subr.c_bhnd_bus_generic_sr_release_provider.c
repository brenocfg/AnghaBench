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
 int /*<<< orphan*/  BHND_BUS_RELEASE_PROVIDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bhnd_service_registry_release (struct bhnd_service_registry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

void
bhnd_bus_generic_sr_release_provider(device_t dev, device_t child,
    device_t provider, bhnd_service_t service)
{
	struct bhnd_service_registry	*bsr;

	bsr = BHND_BUS_GET_SERVICE_REGISTRY(dev, child);
	KASSERT(bsr != NULL, ("NULL service registry"));

	/* Release the provider reference; if the refcount hits zero on an
	 * inherited reference, true will be returned, and we need to drop
	 * our own bus reference to the provider */
	if (!bhnd_service_registry_release(bsr, provider, service))
		return;

	/* Drop our reference to the borrowed provider */
	BHND_BUS_RELEASE_PROVIDER(device_get_parent(dev), dev, provider,
	    service);
}