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
typedef  int u16 ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_LINK_CAP_ASPM ; 
 int PCIEM_LINK_CTL_ASPMC ; 
 int PCIER_LINK_CAP ; 
 int PCIER_LINK_CTL ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
em_disable_aspm(struct adapter *adapter)
{
	int base, reg;
	u16 link_cap,link_ctrl;
	device_t dev = adapter->dev;

	switch (adapter->hw.mac.type) {
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		break;
	default:
		return;
	}
	if (pci_find_cap(dev, PCIY_EXPRESS, &base) != 0)
		return;
	reg = base + PCIER_LINK_CAP;
	link_cap = pci_read_config(dev, reg, 2);
	if ((link_cap & PCIEM_LINK_CAP_ASPM) == 0)
		return;
	reg = base + PCIER_LINK_CTL;
	link_ctrl = pci_read_config(dev, reg, 2);
	link_ctrl &= ~PCIEM_LINK_CTL_ASPMC;
	pci_write_config(dev, reg, link_ctrl, 2);
	return;
}