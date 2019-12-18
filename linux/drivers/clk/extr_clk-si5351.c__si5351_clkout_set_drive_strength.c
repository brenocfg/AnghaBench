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
typedef  int /*<<< orphan*/  u8 ;
struct si5351_driver_data {int dummy; } ;
typedef  enum si5351_drive_strength { ____Placeholder_si5351_drive_strength } si5351_drive_strength ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SI5351_CLK0_CTRL ; 
 int /*<<< orphan*/  SI5351_CLK_DRIVE_STRENGTH_2MA ; 
 int /*<<< orphan*/  SI5351_CLK_DRIVE_STRENGTH_4MA ; 
 int /*<<< orphan*/  SI5351_CLK_DRIVE_STRENGTH_6MA ; 
 int /*<<< orphan*/  SI5351_CLK_DRIVE_STRENGTH_8MA ; 
 int /*<<< orphan*/  SI5351_CLK_DRIVE_STRENGTH_MASK ; 
#define  SI5351_DRIVE_2MA 131 
#define  SI5351_DRIVE_4MA 130 
#define  SI5351_DRIVE_6MA 129 
#define  SI5351_DRIVE_8MA 128 
 int /*<<< orphan*/  si5351_set_bits (struct si5351_driver_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _si5351_clkout_set_drive_strength(
	struct si5351_driver_data *drvdata, int num,
	enum si5351_drive_strength drive)
{
	u8 mask;

	if (num > 8)
		return -EINVAL;

	switch (drive) {
	case SI5351_DRIVE_2MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_2MA;
		break;
	case SI5351_DRIVE_4MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_4MA;
		break;
	case SI5351_DRIVE_6MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_6MA;
		break;
	case SI5351_DRIVE_8MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_8MA;
		break;
	default:
		return 0;
	}

	si5351_set_bits(drvdata, SI5351_CLK0_CTRL + num,
			SI5351_CLK_DRIVE_STRENGTH_MASK, mask);
	return 0;
}