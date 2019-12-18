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
typedef  int u16 ;
struct TYPE_2__ {int addr; struct mii_bus* bus; } ;
struct phy_device {int phy_id; TYPE_1__ mdio; } ;
struct mii_bus {int (* read ) (struct mii_bus*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADM_SIG0 ; 
 int ADM_SIG0_MASK ; 
 int ADM_SIG0_VAL ; 
 int /*<<< orphan*/  ADM_SIG1 ; 
 int ADM_SIG1_MASK ; 
 int ADM_SIG1_VAL ; 
 int /*<<< orphan*/  PHYADDR (int /*<<< orphan*/ ) ; 
 int stub1 (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int stub2 (struct mii_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm6996_fixup(struct phy_device *dev)
{
	struct mii_bus *bus = dev->mdio.bus;
	u16 reg;

	/* Our custom registers are at PHY addresses 0-10. Claim those. */
	if (dev->mdio.addr > 10)
		return 0;

	/* look for the switch on the bus */
	reg = bus->read(bus, PHYADDR(ADM_SIG0)) & ADM_SIG0_MASK;
	if (reg != ADM_SIG0_VAL)
		return 0;

	reg = bus->read(bus, PHYADDR(ADM_SIG1)) & ADM_SIG1_MASK;
	if (reg != ADM_SIG1_VAL)
		return 0;

	dev->phy_id = (ADM_SIG0_VAL << 16) | ADM_SIG1_VAL;

	return 0;
}