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
struct TYPE_2__ {int size; int /*<<< orphan*/  methods; int /*<<< orphan*/  name; } ;
struct pci_driver {int /*<<< orphan*/  bsdclass; TYPE_1__ bsddriver; int /*<<< orphan*/  name; int /*<<< orphan*/  links; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PASS_DEFAULT ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  curthread ; 
 int devclass_add_driver (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_set_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_drivers ; 
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  pci_methods ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_linux_pci_register_driver(struct pci_driver *pdrv, devclass_t dc)
{
	int error;

	linux_set_current(curthread);
	spin_lock(&pci_lock);
	list_add(&pdrv->links, &pci_drivers);
	spin_unlock(&pci_lock);
	pdrv->bsddriver.name = pdrv->name;
	pdrv->bsddriver.methods = pci_methods;
	pdrv->bsddriver.size = sizeof(struct pci_dev);

	mtx_lock(&Giant);
	error = devclass_add_driver(dc, &pdrv->bsddriver,
	    BUS_PASS_DEFAULT, &pdrv->bsdclass);
	mtx_unlock(&Giant);
	return (-error);
}