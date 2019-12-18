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
struct TYPE_2__ {int obd_node; } ;
struct mv_pcib_ctrl_devinfo {int /*<<< orphan*/  di_rl; TYPE_1__ di_dinfo; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct mv_pcib_ctrl_devinfo*) ; 
 struct mv_pcib_ctrl_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
mv_pcib_ctrl_add_child(device_t dev, u_int order, const char *name, int unit)
{
	device_t cdev;
	struct mv_pcib_ctrl_devinfo *di;

	cdev = device_add_child_ordered(dev, order, name, unit);
	if (cdev == NULL)
		return (NULL);

	di = malloc(sizeof(*di), M_DEVBUF, M_WAITOK | M_ZERO);
	di->di_dinfo.obd_node = -1;
	resource_list_init(&di->di_rl);
	device_set_ivars(cdev, di);

	return (cdev);
}