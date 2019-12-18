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
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int aq100x_set_defaults (struct cphy*) ; 
 int t3_phy_reset (struct cphy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aq100x_reset(struct cphy *phy, int wait)
{
	int err;
	err = t3_phy_reset(phy, MDIO_DEV_PMA_PMD, wait);
	if (!err)
		err = aq100x_set_defaults(phy);
	return (err);
}