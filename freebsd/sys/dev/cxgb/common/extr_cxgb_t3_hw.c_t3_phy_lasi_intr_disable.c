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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int t3_phy_lasi_intr_disable(struct cphy *phy)
{
	return mdio_write(phy, MDIO_DEV_PMA_PMD, LASI_CTRL, 0);
}