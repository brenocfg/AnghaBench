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
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_ISOLATE ; 
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  CROSSOVER_AUTO ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  mv88e1xxx_crossover_set (struct cphy*,int /*<<< orphan*/ ) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mv88e1xxx_autoneg_enable(struct cphy *cphy)
{
	mv88e1xxx_crossover_set(cphy, CROSSOVER_AUTO);

	/* restart autoneg for change to take effect */
	return t3_mdio_change_bits(cphy, 0, MII_BMCR, BMCR_PDOWN | BMCR_ISOLATE,
			 	   BMCR_ANENABLE | BMCR_ANRESTART);
}