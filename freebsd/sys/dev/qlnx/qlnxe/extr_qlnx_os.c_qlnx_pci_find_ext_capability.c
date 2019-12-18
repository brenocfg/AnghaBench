#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*) ; 
 scalar_t__ pci_find_extcap (int /*<<< orphan*/ ,int,int*) ; 

int
qlnx_pci_find_ext_capability(void *ecore_dev, int ext_cap)
{
	int		reg;
	qlnx_host_t	*ha;

	ha = ecore_dev;

	if (pci_find_extcap(ha->pci_dev, ext_cap, &reg) == 0)
		return reg;
	else {
		QL_DPRINT1(ha, "failed\n");
		return 0;
	}
}