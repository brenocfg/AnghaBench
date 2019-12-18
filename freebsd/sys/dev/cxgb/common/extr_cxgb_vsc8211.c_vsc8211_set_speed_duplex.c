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
 int t3_set_phy_speed_duplex (struct cphy*,int,int) ; 
 int vsc8211_set_automdi (struct cphy*,int) ; 

__attribute__((used)) static int vsc8211_set_speed_duplex(struct cphy *phy, int speed, int duplex)
{
	int err;

	err = t3_set_phy_speed_duplex(phy, speed, duplex);
	if (!err)
		err = vsc8211_set_automdi(phy, 1);
	return err;
}