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
struct macio_chip {scalar_t__ type; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  KEYLARGO_GPIO_OUTOUT_DATA ; 
 int /*<<< orphan*/  KEYLARGO_GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  KL_GPIO_ETH_PHY_RESET ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_IN8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_chips ; 
 scalar_t__ macio_intrepid ; 
 scalar_t__ macio_keylargo ; 
 scalar_t__ macio_pangea ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static long
core99_gmac_phy_reset(struct device_node *node, long param, long value)
{
	unsigned long flags;
	struct macio_chip *macio;

	macio = &macio_chips[0];
	if (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_intrepid)
		return -ENODEV;

	LOCK(flags);
	MACIO_OUT8(KL_GPIO_ETH_PHY_RESET, KEYLARGO_GPIO_OUTPUT_ENABLE);
	(void)MACIO_IN8(KL_GPIO_ETH_PHY_RESET);
	UNLOCK(flags);
	mdelay(10);
	LOCK(flags);
	MACIO_OUT8(KL_GPIO_ETH_PHY_RESET, /*KEYLARGO_GPIO_OUTPUT_ENABLE | */
		KEYLARGO_GPIO_OUTOUT_DATA);
	UNLOCK(flags);
	mdelay(10);

	return 0;
}