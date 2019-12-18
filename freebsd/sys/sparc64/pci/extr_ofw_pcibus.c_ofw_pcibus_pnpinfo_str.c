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
 int /*<<< orphan*/  ofw_bus_gen_child_pnpinfo_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_child_pnpinfo_str_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static int
ofw_pcibus_pnpinfo_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{

	pci_child_pnpinfo_str_method(dev, child, buf, buflen);
	if (ofw_bus_get_node(child) != -1)  {
		strlcat(buf, " ", buflen); /* Separate info. */
		ofw_bus_gen_child_pnpinfo_str(dev, child, buf, buflen);
	}

	return (0);
}