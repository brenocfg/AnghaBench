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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_2__ {size_t lane_mapping; } ;

/* Variables and functions */
 int CPHY_SATA_TX_ATTEN ; 
 int CPHY_SATA_TX_ATTEN_SHIFT ; 
 int CPHY_SATA_TX_OVERRIDE ; 
 scalar_t__ CPHY_TX_INPUT_STS ; 
 scalar_t__ CPHY_TX_OVERRIDE ; 
 size_t SPHY_LANE ; 
 int combo_phy_read (size_t,scalar_t__) ; 
 int /*<<< orphan*/  combo_phy_write (size_t,scalar_t__,int) ; 
 TYPE_1__* port_data ; 

__attribute__((used)) static void cphy_override_tx_attenuation(u8 sata_port, u32 val)
{
	u8 lane = port_data[sata_port].lane_mapping;
	u32 tmp;

	if (val & 0x8)
		return;

	tmp = combo_phy_read(sata_port, CPHY_TX_INPUT_STS + lane * SPHY_LANE);
	tmp &= ~CPHY_SATA_TX_OVERRIDE;
	combo_phy_write(sata_port, CPHY_TX_OVERRIDE + lane * SPHY_LANE, tmp);

	tmp |= CPHY_SATA_TX_OVERRIDE;
	combo_phy_write(sata_port, CPHY_TX_OVERRIDE + lane * SPHY_LANE, tmp);

	tmp |= (val << CPHY_SATA_TX_ATTEN_SHIFT) & CPHY_SATA_TX_ATTEN;
	combo_phy_write(sata_port, CPHY_TX_OVERRIDE + lane * SPHY_LANE, tmp);
}