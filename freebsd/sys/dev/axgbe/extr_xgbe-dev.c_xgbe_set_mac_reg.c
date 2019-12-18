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
typedef  char u8 ;
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE ; 
 int /*<<< orphan*/  MAC_MACA1HR ; 
 scalar_t__ MAC_MACA_INC ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_set_mac_reg(struct xgbe_prv_data *pdata,
			     char *addr, unsigned int *mac_reg)
{
	unsigned int mac_addr_hi, mac_addr_lo;
	u8 *mac_addr;

	mac_addr_lo = 0;
	mac_addr_hi = 0;

	if (addr) {
		mac_addr = (u8 *)&mac_addr_lo;
		mac_addr[0] = addr[0];
		mac_addr[1] = addr[1];
		mac_addr[2] = addr[2];
		mac_addr[3] = addr[3];
		mac_addr = (u8 *)&mac_addr_hi;
		mac_addr[0] = addr[4];
		mac_addr[1] = addr[5];

		XGMAC_SET_BITS(mac_addr_hi, MAC_MACA1HR, AE, 1);
	}

	XGMAC_IOWRITE(pdata, *mac_reg, mac_addr_hi);
	*mac_reg += MAC_MACA_INC;
	XGMAC_IOWRITE(pdata, *mac_reg, mac_addr_lo);
	*mac_reg += MAC_MACA_INC;
}