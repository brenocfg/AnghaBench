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
 int /*<<< orphan*/  LASI_STAT ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int cphy_cause_link_change ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int t3_phy_lasi_intr_handler(struct cphy *phy)
{
	unsigned int status;
	int err = mdio_read(phy, MDIO_DEV_PMA_PMD, LASI_STAT, &status);

	if (err)
		return err;
	return (status & 1) ?  cphy_cause_link_change : 0;
}