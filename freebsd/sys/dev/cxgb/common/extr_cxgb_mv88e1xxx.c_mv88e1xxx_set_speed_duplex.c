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
 int mv88e1xxx_reset (struct cphy*,int /*<<< orphan*/ ) ; 
 int t3_set_phy_speed_duplex (struct cphy*,int,int) ; 

__attribute__((used)) static int mv88e1xxx_set_speed_duplex(struct cphy *phy, int speed, int duplex)
{
	int err = t3_set_phy_speed_duplex(phy, speed, duplex);

	/* PHY needs reset for new settings to take effect */
	if (!err)
		err = mv88e1xxx_reset(phy, 0);
	return err;
}