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
struct cphy {int /*<<< orphan*/  addr; int /*<<< orphan*/ * adapter; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_XGM_SERDES_STAT0 ; 
 int /*<<< orphan*/  A_XGM_SERDES_STAT1 ; 
 int /*<<< orphan*/  A_XGM_SERDES_STAT2 ; 
 int /*<<< orphan*/  A_XGM_SERDES_STAT3 ; 
 int DUPLEX_FULL ; 
 unsigned int F_LOWSIG0 ; 
 int PHY_LINK_DOWN ; 
 int PHY_LINK_UP ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  XGM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xaui_direct_get_link_status(struct cphy *phy, int *link_state,
				       int *speed, int *duplex, int *fc)
{
	if (link_state) {
		unsigned int status;
		adapter_t *adapter = phy->adapter;

		status = t3_read_reg(adapter,
				     XGM_REG(A_XGM_SERDES_STAT0, phy->addr)) |
			 t3_read_reg(adapter,
				     XGM_REG(A_XGM_SERDES_STAT1, phy->addr)) |
			 t3_read_reg(adapter,
				     XGM_REG(A_XGM_SERDES_STAT2, phy->addr)) |
			 t3_read_reg(adapter,
				     XGM_REG(A_XGM_SERDES_STAT3, phy->addr));
		*link_state = status & F_LOWSIG0 ? PHY_LINK_DOWN : PHY_LINK_UP;
	}
	if (speed)
		*speed = SPEED_10000;
	if (duplex)
		*duplex = DUPLEX_FULL;
	return 0;
}