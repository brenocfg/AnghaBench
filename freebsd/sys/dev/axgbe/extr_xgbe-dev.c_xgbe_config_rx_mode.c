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
 int /*<<< orphan*/  xgbe_add_mac_addresses (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_set_all_multicast_mode (struct xgbe_prv_data*,unsigned int) ; 
 int /*<<< orphan*/  xgbe_set_promiscuous_mode (struct xgbe_prv_data*,unsigned int) ; 

__attribute__((used)) static int xgbe_config_rx_mode(struct xgbe_prv_data *pdata)
{
	unsigned int pr_mode, am_mode;

	/* XXX */
	pr_mode = 0;
	am_mode = 0;

	xgbe_set_promiscuous_mode(pdata, pr_mode);
	xgbe_set_all_multicast_mode(pdata, am_mode);

	xgbe_add_mac_addresses(pdata);

	return 0;
}