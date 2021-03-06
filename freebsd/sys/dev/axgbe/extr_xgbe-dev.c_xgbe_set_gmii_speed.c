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
 int /*<<< orphan*/  MAC_TCR ; 
 int /*<<< orphan*/  SS ; 
 int XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xgbe_set_gmii_speed(struct xgbe_prv_data *pdata)
{
	if (XGMAC_IOREAD_BITS(pdata, MAC_TCR, SS) == 0x3)
		return 0;

	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, SS, 0x3);

	return 0;
}