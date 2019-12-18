#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__ pci_direct_conf1 ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 TYPE_1__* raw_pci_ext_ops ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ type1_access_ok (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int pci_read(struct pci_bus *bus, unsigned int devfn, int where,
		    int size, u32 *value)
{
	if (type1_access_ok(bus->number, devfn, where))
		return pci_direct_conf1.read(pci_domain_nr(bus), bus->number,
					devfn, where, size, value);
	return raw_pci_ext_ops->read(pci_domain_nr(bus), bus->number,
			      devfn, where, size, value);
}