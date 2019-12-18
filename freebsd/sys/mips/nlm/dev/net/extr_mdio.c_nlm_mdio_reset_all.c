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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_7 ; 
 int /*<<< orphan*/  LANE_CFG ; 
 int /*<<< orphan*/  nlm_gmac_mdio_reset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_int_gmac_mdio_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nlm_mdio_reset_all(uint64_t nae_base)
{
	/* reset internal MDIO */
	nlm_int_gmac_mdio_reset(nae_base, 0, BLOCK_7, LANE_CFG);
	/* reset external MDIO */
	nlm_gmac_mdio_reset(nae_base, 0, BLOCK_7, LANE_CFG);
	nlm_gmac_mdio_reset(nae_base, 1, BLOCK_7, LANE_CFG);
}