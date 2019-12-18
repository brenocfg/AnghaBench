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
struct bhnd_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int BHND_BUS_GET_NVRAM_VAR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int BHND_NVRAM_GETVAR (int /*<<< orphan*/ *,char const*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_SERVICE_NVRAM ; 
 int ENODEV ; 
 int /*<<< orphan*/  bhnd_release_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_retain_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct bhnd_softc* device_get_softc (int /*<<< orphan*/ *) ; 

int
bhnd_generic_get_nvram_var(device_t dev, device_t child, const char *name,
    void *buf, size_t *size, bhnd_nvram_type type)
{
	struct bhnd_softc	*sc;
	device_t		 nvram, parent;
	int			 error;

	sc = device_get_softc(dev);

	/* If a NVRAM device is available, consult it first */
	nvram = bhnd_retain_provider(child, BHND_SERVICE_NVRAM);
	if (nvram != NULL) {
		error = BHND_NVRAM_GETVAR(nvram, name, buf, size, type);
		bhnd_release_provider(child, nvram, BHND_SERVICE_NVRAM);
		return (error);
	}

	/* Otherwise, try to delegate to parent */
	if ((parent = device_get_parent(dev)) == NULL)
		return (ENODEV);

	return (BHND_BUS_GET_NVRAM_VAR(device_get_parent(dev), child,
	    name, buf, size, type));
}