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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PFR ; 
 int /*<<< orphan*/  PR ; 
 unsigned int XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_filtering (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_set_promiscuous_mode(struct xgbe_prv_data *pdata,
				     unsigned int enable)
{
	unsigned int val = enable ? 1 : 0;

	if (XGMAC_IOREAD_BITS(pdata, MAC_PFR, PR) == val)
		return 0;

	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, PR, val);

	/* Hardware will still perform VLAN filtering in promiscuous mode */
	xgbe_disable_rx_vlan_filtering(pdata);

	return 0;
}