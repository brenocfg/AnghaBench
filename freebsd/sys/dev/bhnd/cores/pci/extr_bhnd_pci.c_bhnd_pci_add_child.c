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
typedef  int /*<<< orphan*/  u_int ;
struct bhnd_pci_devinfo {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct bhnd_pci_devinfo*) ; 
 struct bhnd_pci_devinfo* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
bhnd_pci_add_child(device_t dev, u_int order, const char *name, int unit)
{
	struct bhnd_pci_devinfo	*dinfo;
	device_t		 child;
	
	child = device_add_child_ordered(dev, order, name, unit);
	if (child == NULL)
		return (NULL);

	dinfo = malloc(sizeof(struct bhnd_pci_devinfo), M_DEVBUF, M_NOWAIT);
	if (dinfo == NULL) {
		device_delete_child(dev, child);
		return (NULL);
	}

	resource_list_init(&dinfo->resources);
	
	device_set_ivars(child, dinfo);
	return (child);
}