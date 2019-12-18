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
struct bhnd_nvram_cfe_softc {int /*<<< orphan*/  store; int /*<<< orphan*/  dev; } ;
struct bcm_platform {int /*<<< orphan*/  services; int /*<<< orphan*/ * nvram_cls; int /*<<< orphan*/ * nvram_io; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_SERVICE_NVRAM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct bcm_platform* bcm_get_platform () ; 
 int /*<<< orphan*/  bhnd_nvram_store_free (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_store_parse_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bhnd_service_registry_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhnd_nvram_cfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_cfe_attach(device_t dev)
{
	struct bcm_platform		*bp;
	struct bhnd_nvram_cfe_softc	*sc;
	int				 error;

	bp = bcm_get_platform();
	KASSERT(bp->nvram_io != NULL, ("missing NVRAM I/O context"));
	KASSERT(bp->nvram_cls != NULL, ("missing NVRAM class"));

	sc = device_get_softc(dev);
	sc->dev = dev;

	error = bhnd_nvram_store_parse_new(&sc->store, bp->nvram_io,
	    bp->nvram_cls);
	if (error)
		return (error);

	error = bhnd_service_registry_add(&bp->services, dev,
	    BHND_SERVICE_NVRAM, 0);
	if (error) {
		bhnd_nvram_store_free(sc->store);
		return (error);
	}

	return (error);
}