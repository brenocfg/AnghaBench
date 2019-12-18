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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMADA_37XX_NB_DFS_EN ; 
 unsigned int ARMADA_37XX_NB_DYN_MOD ; 
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,unsigned int,unsigned int*) ; 

__attribute__((used)) static bool armada_3700_pm_dvfs_is_enabled(struct regmap *base)
{
	unsigned int val, reg = ARMADA_37XX_NB_DYN_MOD;

	if (IS_ERR(base))
		return false;

	regmap_read(base, reg, &val);

	return !!(val & BIT(ARMADA_37XX_NB_DFS_EN));
}