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
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_10GBR_PMD_CTRL ; 
 unsigned int XGBE_KR_TRAINING_ENABLE ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void xgbe_an_enable_kr_training(struct xgbe_prv_data *pdata)
{
	unsigned int reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);

	reg |= XGBE_KR_TRAINING_ENABLE;
	XMDIO_WRITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);
}