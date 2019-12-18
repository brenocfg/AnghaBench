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
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_domain (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int,int,int,int) ; 

int
pci_child_location_str_method(device_t dev, device_t child, char *buf,
    size_t buflen)
{

	snprintf(buf, buflen, "slot=%d function=%d dbsf=pci%d:%d:%d:%d",
	    pci_get_slot(child), pci_get_function(child), pci_get_domain(child),
	    pci_get_bus(child), pci_get_slot(child), pci_get_function(child));
	return (0);
}