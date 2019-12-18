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
struct TYPE_2__ {int domain; int bus; int slot; int func; int /*<<< orphan*/  dev; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
pci_print_faulted_dev_name(const struct pci_devinfo *dinfo)
{
	const char *dev_name;
	device_t dev;

	dev = dinfo->cfg.dev;
	printf("pci%d:%d:%d:%d", dinfo->cfg.domain, dinfo->cfg.bus,
	    dinfo->cfg.slot, dinfo->cfg.func);
	dev_name = device_get_name(dev);
	if (dev_name != NULL)
		printf(" (%s%d)", dev_name, device_get_unit(dev));
}