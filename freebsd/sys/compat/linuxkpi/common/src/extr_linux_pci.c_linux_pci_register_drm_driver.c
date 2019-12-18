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
struct pci_driver {int isdrm; char* name; } ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int ENXIO ; 
 int _linux_pci_register_driver (struct pci_driver*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devclass_create (char*) ; 

int
linux_pci_register_drm_driver(struct pci_driver *pdrv)
{
	devclass_t dc;

	dc = devclass_create("vgapci");
	if (dc == NULL)
		return (-ENXIO);
	pdrv->isdrm = true;
	pdrv->name = "drmn";
	return (_linux_pci_register_driver(pdrv, dc));
}