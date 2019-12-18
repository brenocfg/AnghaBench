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
typedef  int u8 ;
struct s3c24xx_clkout {int mask; int shift; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c2410_modify_misccr (int,int) ; 
 struct s3c24xx_clkout* to_s3c24xx_clkout (struct clk_hw*) ; 

__attribute__((used)) static int s3c24xx_clkout_set_parent(struct clk_hw *hw, u8 index)
{
	struct s3c24xx_clkout *clkout = to_s3c24xx_clkout(hw);

	s3c2410_modify_misccr((clkout->mask << clkout->shift),
			      (index << clkout->shift));

	return 0;
}