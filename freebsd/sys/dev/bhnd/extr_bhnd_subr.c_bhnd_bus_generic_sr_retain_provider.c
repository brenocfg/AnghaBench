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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bhnd_service_t ;

/* Variables and functions */
 struct bhnd_service_registry* BHND_BUS_GET_SERVICE_REGISTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BHND_BUS_RELEASE_PROVIDER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BHND_BUS_RETAIN_PROVIDER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_SPF_INHERITED ; 
 int EEXIST ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int bhnd_service_registry_add (struct bhnd_service_registry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_service_registry_retain (struct bhnd_service_registry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int) ; 

device_t
bhnd_bus_generic_sr_retain_provider(device_t dev, device_t child,
    bhnd_service_t service)
{
	struct bhnd_service_registry	*bsr;
	device_t			 parent, provider;
	int				 error;

	bsr = BHND_BUS_GET_SERVICE_REGISTRY(dev, child);
	KASSERT(bsr != NULL, ("NULL service registry"));

	/*
	 * Attempt to fetch a service provider reference from either the local
	 * service registry, or if not found, from our parent.
	 * 
	 * If we fetch a provider from our parent, we register the provider
	 * with the local service registry to prevent conflicting local
	 * registrations from being added.
	 */
	while (1) {
		/* Check the local service registry first */
		provider = bhnd_service_registry_retain(bsr, service);
		if (provider != NULL)
			return (provider);

		/* Otherwise, try to delegate to our parent (if any) */
		if ((parent = device_get_parent(dev)) == NULL)
			return (NULL);

		provider = BHND_BUS_RETAIN_PROVIDER(parent, dev, service);
		if (provider == NULL)
			return (NULL);

		/* Register the inherited service registration with the local
		 * registry */
		error = bhnd_service_registry_add(bsr, provider, service,
		    BHND_SPF_INHERITED);
		if (error) {
			BHND_BUS_RELEASE_PROVIDER(parent, dev, provider,
			    service);
			if (error == EEXIST) {
				/* A valid service provider was registered
				 * concurrently; retry fetching from the local
				 * registry */
				continue;
			}

			device_printf(dev, "failed to register service "
			    "provider: %d\n", error);
			return (NULL);
		}
	}
}