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
struct bhnd_sprom_softc {int /*<<< orphan*/  store; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_SERVICE_ANY ; 
 int bhnd_deregister_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_store_free (int /*<<< orphan*/ ) ; 
 struct bhnd_sprom_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
bhnd_sprom_detach(device_t dev)
{
	struct bhnd_sprom_softc	*sc;
	int			 error;
	
	sc = device_get_softc(dev);

	if ((error = bhnd_deregister_provider(dev, BHND_SERVICE_ANY)))
		return (error);

	bhnd_nvram_store_free(sc->store);

	return (0);
}