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
struct pcicfg_iov {int dummy; } ;
struct TYPE_2__ {int flags; struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCICFG_VF ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_iov_is_child_vf(struct pcicfg_iov *pf, device_t child)
{
	struct pci_devinfo *vfinfo;

	vfinfo = device_get_ivars(child);

	if (!(vfinfo->cfg.flags & PCICFG_VF))
		return (0);

	return (pf == vfinfo->cfg.iov);
}