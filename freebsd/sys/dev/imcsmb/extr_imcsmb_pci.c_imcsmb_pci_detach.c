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
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imcsmb_pci_detach(device_t dev)
{
	int rc;

	/* Detach any attached drivers */
	rc = bus_generic_detach(dev);
	if (rc == 0) {
		/* Remove all children */
		rc = device_delete_children(dev);
	}

	return (rc);
}