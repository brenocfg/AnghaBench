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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MV_GLOBAL_STATUS_REG ; 
 int MV_STATUS_PHY_LINK_UP ; 
 int MV_STATUS_RDLH_LINK_UP ; 
 int pci_dw_dbi_rd4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_mv_get_link(device_t dev, bool *status)
{
	uint32_t reg;

	reg = pci_dw_dbi_rd4(dev, MV_GLOBAL_STATUS_REG);
	if ((reg & (MV_STATUS_RDLH_LINK_UP | MV_STATUS_PHY_LINK_UP)) ==
	    (MV_STATUS_RDLH_LINK_UP | MV_STATUS_PHY_LINK_UP))
		*status = true;
	else
		*status = false;

	return (0);
}