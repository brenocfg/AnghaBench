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
 int /*<<< orphan*/  AEL2020_GPIO_INTR ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int t3_phy_lasi_intr_clear (struct cphy*) ; 

__attribute__((used)) static int ael2020_intr_clear(struct cphy *phy)
{
	unsigned int stat;
	int err = mdio_read(phy, MDIO_DEV_PMA_PMD, AEL2020_GPIO_INTR, &stat);
	return err ? err : t3_phy_lasi_intr_clear(phy);
}