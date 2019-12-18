#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int obd_node; int /*<<< orphan*/  obd_name; } ;
struct nexus_devinfo {int /*<<< orphan*/  ndi_rl; TYPE_1__ ndi_obdinfo; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct nexus_devinfo*) ; 
 struct nexus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
nexus_add_child(device_t dev, u_int order, const char *name, int unit)
{
	device_t cdev;
	struct nexus_devinfo *ndi;

	cdev = device_add_child_ordered(dev, order, name, unit);
	if (cdev == NULL)
		return (NULL);

	ndi = malloc(sizeof(*ndi), M_DEVBUF, M_WAITOK | M_ZERO);
	ndi->ndi_obdinfo.obd_node = -1;
	ndi->ndi_obdinfo.obd_name = strdup(name, M_OFWPROP);
	resource_list_init(&ndi->ndi_rl);
	device_set_ivars(cdev, ndi);

	return (cdev);
}