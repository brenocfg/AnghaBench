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
struct twl6040_pdmclk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6040_REG_HPPLLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_LPPLLCTL ; 
 int twl6040_pdmclk_reset_one_clock (struct twl6040_pdmclk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6040_pdmclk_quirk_reset_clocks(struct twl6040_pdmclk *pdmclk)
{
	int ret;

	ret = twl6040_pdmclk_reset_one_clock(pdmclk, TWL6040_REG_HPPLLCTL);
	if (ret)
		return ret;

	ret = twl6040_pdmclk_reset_one_clock(pdmclk, TWL6040_REG_LPPLLCTL);
	if (ret)
		return ret;

	return 0;
}