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
struct bhnd_nvram_cfe_softc {int /*<<< orphan*/  store; } ;
struct bcm_platform {int /*<<< orphan*/  services; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_SERVICE_ANY ; 
 struct bcm_platform* bcm_get_platform () ; 
 int /*<<< orphan*/  bhnd_nvram_store_free (int /*<<< orphan*/ ) ; 
 int bhnd_service_registry_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhnd_nvram_cfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_cfe_detach(device_t dev)
{
	struct bcm_platform		*bp;
	struct bhnd_nvram_cfe_softc	*sc;
	int				 error;

	bp = bcm_get_platform();
	sc = device_get_softc(dev);

	error = bhnd_service_registry_remove(&bp->services, dev,
	    BHND_SERVICE_ANY);
	if (error)
		return (error);

	bhnd_nvram_store_free(sc->store);

	return (0);
}