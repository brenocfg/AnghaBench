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
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CTRL2 ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 unsigned int MDIO_PCS_CTRL2_10GBR ; 
 unsigned int MDIO_PCS_CTRL2_TYPE ; 
 int XGBE_MODE_KR ; 
 int XGBE_MODE_KX ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_cur_mode(struct xgbe_prv_data *pdata,
			  enum xgbe_mode *mode)
{
	unsigned int reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL2);
	if ((reg & MDIO_PCS_CTRL2_TYPE) == MDIO_PCS_CTRL2_10GBR)
		*mode = XGBE_MODE_KR;
	else
		*mode = XGBE_MODE_KX;
}