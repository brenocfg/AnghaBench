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
 int /*<<< orphan*/  MODULE_DEV_ADDR ; 
 int ael_i2c_rd (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_transtype_unknown ; 

__attribute__((used)) static int get_phytrans_type(struct cphy *phy)
{
	int v;

	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 0);
	if (v < 0)
		return phy_transtype_unknown;

	return v;
}