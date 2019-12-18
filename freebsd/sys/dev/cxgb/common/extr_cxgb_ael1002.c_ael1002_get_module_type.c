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
 int ETIMEDOUT ; 
 int ael2xxx_get_module_type (struct cphy*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int phy_modtype_none ; 

__attribute__((used)) static int ael1002_get_module_type(struct cphy *phy, int delay_ms)
{
	int v;

	if (delay_ms)
		msleep(delay_ms);

	v = ael2xxx_get_module_type(phy, delay_ms);

	return (v == -ETIMEDOUT ? phy_modtype_none : v);
}