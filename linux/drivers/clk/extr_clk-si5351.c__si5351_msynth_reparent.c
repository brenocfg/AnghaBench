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
struct si5351_driver_data {int dummy; } ;
typedef  enum si5351_multisynth_src { ____Placeholder_si5351_multisynth_src } si5351_multisynth_src ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SI5351_CLK0_CTRL ; 
 int /*<<< orphan*/  SI5351_CLK_PLL_SELECT ; 
 int SI5351_MULTISYNTH_SRC_DEFAULT ; 
 int SI5351_MULTISYNTH_SRC_VCO0 ; 
 int /*<<< orphan*/  si5351_set_bits (struct si5351_driver_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _si5351_msynth_reparent(struct si5351_driver_data *drvdata,
				   int num, enum si5351_multisynth_src parent)
{
	if (parent == SI5351_MULTISYNTH_SRC_DEFAULT)
		return 0;

	if (num > 8)
		return -EINVAL;

	si5351_set_bits(drvdata, SI5351_CLK0_CTRL + num, SI5351_CLK_PLL_SELECT,
			(parent == SI5351_MULTISYNTH_SRC_VCO0) ? 0 :
			SI5351_CLK_PLL_SELECT);
	return 0;
}