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
struct pcifront_device {TYPE_1__* xdev; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {unsigned int otherend_id; int /*<<< orphan*/  otherend; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (TYPE_1__*,int,char*,...) ; 
 int xenbus_scanf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static int
xpcife_attach(device_t dev) 
{
	struct pcifront_device *pdev = (struct pcifront_device *)device_get_ivars(dev);
	int i, num_roots, len, err;
	char str[64];
	unsigned int domain, bus;

	DPRINTF("xpcife attach (unit=%d)\n", pdev->unit);

	err = xenbus_scanf(NULL, pdev->xdev->otherend,
					   "root_num", "%d", &num_roots);
	if (err != 1) {
		if (err == 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
						 "Error reading number of PCI roots");
		goto out;
	}

	/* Add a pcib device for each root */
	for (i = 0; i < num_roots; i++) {
		device_t child;

		len = snprintf(str, sizeof(str), "root-%d", i);
		if (unlikely(len >= (sizeof(str) - 1))) {
			err = -ENOMEM;
			goto out;
		}

		err = xenbus_scanf(NULL, pdev->xdev->otherend, str,
						   "%x:%x", &domain, &bus);
		if (err != 2) {
			if (err >= 0)
				err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
							 "Error reading PCI root %d", i);
			goto out;
		}
		err = 0;
		if (domain != pdev->xdev->otherend_id) {
			err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
							 "Domain mismatch %d != %d", domain, pdev->xdev->otherend_id);
			goto out;
		}
		
		child = device_add_child(dev, "pcib", bus);
		if (!child) {
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
							 "Unable to create pcib%d", bus);
			goto out;
		}
	}

 out:
	return bus_generic_attach(dev);
}