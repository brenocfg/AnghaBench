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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int BHND_BUS_GET_NVRAM_VAR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int BHND_NVRAM_GETVAR (int /*<<< orphan*/ *,char const*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

int
bhnd_bus_generic_get_nvram_var(device_t dev, device_t child, const char *name,
    void *buf, size_t *size, bhnd_nvram_type type)
{
	device_t	nvram;
	device_t	parent;

        /* Make sure we're holding Giant for newbus */
	GIANT_REQUIRED;

	/* Look for a directly-attached NVRAM child */
	if ((nvram = device_find_child(dev, "bhnd_nvram", -1)) != NULL)
		return BHND_NVRAM_GETVAR(nvram, name, buf, size, type);

	/* Try to delegate to parent */
	if ((parent = device_get_parent(dev)) == NULL)
		return (ENODEV);

	return (BHND_BUS_GET_NVRAM_VAR(device_get_parent(dev), child,
	    name, buf, size, type));
}