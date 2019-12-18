#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  obd_name; } ;
struct vdevice_devinfo {TYPE_1__ mdi_obdinfo; int /*<<< orphan*/  mdi_resources; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct vdevice_devinfo*) ; 
 int /*<<< orphan*/  free (struct vdevice_devinfo*,int /*<<< orphan*/ ) ; 
 struct vdevice_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_1__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powerpc_register_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_pic ; 

__attribute__((used)) static int 
vdevice_attach(device_t dev) 
{
	phandle_t root, child;
	device_t cdev;
	struct vdevice_devinfo *dinfo;

	root = ofw_bus_get_node(dev);

	/* The XICP (root PIC) will handle all our interrupts */
	powerpc_register_pic(root_pic, OF_xref_from_node(root),
	    1 << 24 /* 24-bit XIRR field */, 1 /* Number of IPIs */, FALSE);

	for (child = OF_child(root); child != 0; child = OF_peer(child)) {
		dinfo = malloc(sizeof(*dinfo), M_DEVBUF, M_WAITOK | M_ZERO);

                if (ofw_bus_gen_setup_devinfo(&dinfo->mdi_obdinfo,
		    child) != 0) {
                        free(dinfo, M_DEVBUF);
                        continue;
                }
		resource_list_init(&dinfo->mdi_resources);

		ofw_bus_intr_to_rl(dev, child, &dinfo->mdi_resources, NULL);

                cdev = device_add_child(dev, NULL, -1);
                if (cdev == NULL) {
                        device_printf(dev, "<%s>: device_add_child failed\n",
                            dinfo->mdi_obdinfo.obd_name);
                        ofw_bus_gen_destroy_devinfo(&dinfo->mdi_obdinfo);
                        free(dinfo, M_DEVBUF);
                        continue;
                }
		device_set_ivars(cdev, dinfo);
	}

	return (bus_generic_attach(dev));
}