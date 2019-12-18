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
struct xgbe_prv_data {int /*<<< orphan*/  an_mutex; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_LINK_ERR ; 
 int __xgbe_phy_config_aneg (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xgbe_phy_config_aneg(struct xgbe_prv_data *pdata)
{
	int ret;

	sx_xlock(&pdata->an_mutex);

	ret = __xgbe_phy_config_aneg(pdata);
	if (ret)
		set_bit(XGBE_LINK_ERR, &pdata->dev_state);
	else
		clear_bit(XGBE_LINK_ERR, &pdata->dev_state);

	sx_unlock(&pdata->an_mutex);

	return ret;
}