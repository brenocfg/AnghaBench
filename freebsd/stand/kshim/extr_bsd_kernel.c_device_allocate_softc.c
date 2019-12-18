#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module_data {TYPE_1__* driver; } ;
typedef  TYPE_2__* device_t ;
struct TYPE_5__ {int dev_softc_alloc; int /*<<< orphan*/ * dev_sc; struct module_data* dev_module; } ;
struct TYPE_4__ {scalar_t__ size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
device_allocate_softc(device_t dev)
{
	const struct module_data *mod;

	mod = dev->dev_module;

	if ((dev->dev_softc_alloc == 0) &&
	    (mod->driver->size != 0)) {
		dev->dev_sc = malloc(mod->driver->size,
		    M_DEVBUF, M_WAITOK | M_ZERO);

		if (dev->dev_sc == NULL)
			return (ENOMEM);

		dev->dev_softc_alloc = 1;
	}
	return (0);
}