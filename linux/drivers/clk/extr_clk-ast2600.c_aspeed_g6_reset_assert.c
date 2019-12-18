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
typedef  int /*<<< orphan*/  u32 ;
struct reset_controller_dev {int dummy; } ;
struct aspeed_reset {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_G6_RESET_CTRL ; 
 int /*<<< orphan*/  ASPEED_G6_RESET_CTRL2 ; 
 int /*<<< orphan*/  get_bit (unsigned long) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aspeed_reset* to_aspeed_reset (struct reset_controller_dev*) ; 

__attribute__((used)) static int aspeed_g6_reset_assert(struct reset_controller_dev *rcdev,
				  unsigned long id)
{
	struct aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 rst = get_bit(id);
	u32 reg = id >= 32 ? ASPEED_G6_RESET_CTRL2 : ASPEED_G6_RESET_CTRL;

	return regmap_write(ar->map, reg, rst);
}