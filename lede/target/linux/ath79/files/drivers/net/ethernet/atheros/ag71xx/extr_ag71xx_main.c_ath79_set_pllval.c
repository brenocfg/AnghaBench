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
typedef  scalar_t__ u32 ;
struct ag71xx {int speed; int /*<<< orphan*/  pllregmap; scalar_t__* plldata; scalar_t__* pllreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ath79_set_pllval(struct ag71xx *ag)
{
	u32 pll_reg = ag->pllreg[1];
	u32 pll_val;

	if (!ag->pllregmap)
		return;

	switch (ag->speed) {
	case SPEED_10:
		pll_val = ag->plldata[2];
		break;
	case SPEED_100:
		pll_val = ag->plldata[1];
		break;
	case SPEED_1000:
		pll_val = ag->plldata[0];
		break;
	default:
		BUG();
	}

	if (pll_val)
		regmap_write(ag->pllregmap, pll_reg, pll_val);
}