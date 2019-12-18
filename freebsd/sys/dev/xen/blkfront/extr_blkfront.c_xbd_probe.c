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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ xen_disable_pv_disks ; 
 scalar_t__ xen_hvm_domain () ; 
 int /*<<< orphan*/  xenbus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_get_type (int /*<<< orphan*/ ) ; 
 int xs_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static int
xbd_probe(device_t dev)
{
	if (strcmp(xenbus_get_type(dev), "vbd") != 0)
		return (ENXIO);

	if (xen_hvm_domain() && xen_disable_pv_disks != 0)
		return (ENXIO);

	if (xen_hvm_domain()) {
		int error;
		char *type;

		/*
		 * When running in an HVM domain, IDE disk emulation is
		 * disabled early in boot so that native drivers will
		 * not see emulated hardware.  However, CDROM device
		 * emulation cannot be disabled.
		 *
		 * Through use of FreeBSD's vm_guest and xen_hvm_domain()
		 * APIs, we could modify the native CDROM driver to fail its
		 * probe when running under Xen.  Unfortunatlely, the PV
		 * CDROM support in XenServer (up through at least version
		 * 6.2) isn't functional, so we instead rely on the emulated
		 * CDROM instance, and fail to attach the PV one here in
		 * the blkfront driver.
		 */
		error = xs_read(XST_NIL, xenbus_get_node(dev),
		    "device-type", NULL, (void **) &type);
		if (error)
			return (ENXIO);

		if (strncmp(type, "cdrom", 5) == 0) {
			free(type, M_XENSTORE);
			return (ENXIO);
		}
		free(type, M_XENSTORE);
	}

	device_set_desc(dev, "Virtual Block Device");
	device_quiet(dev);
	return (0);
}