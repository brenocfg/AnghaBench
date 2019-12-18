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
struct TYPE_4__ {int (* read ) (unsigned int,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int (* read ) (unsigned int,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* raw_pci_ext_ops ; 
 TYPE_1__* raw_pci_ops ; 
 int stub1 (unsigned int,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 int stub2 (unsigned int,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *) ; 

int raw_pci_read(unsigned int domain, unsigned int bus, unsigned int devfn,
						int reg, int len, u32 *val)
{
	if (domain == 0 && reg < 256 && raw_pci_ops)
		return raw_pci_ops->read(domain, bus, devfn, reg, len, val);
	if (raw_pci_ext_ops)
		return raw_pci_ext_ops->read(domain, bus, devfn, reg, len, val);
	return -EINVAL;
}