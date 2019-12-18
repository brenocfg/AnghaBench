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
typedef  int /*<<< orphan*/  u64 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST_ULL (int /*<<< orphan*/ ,unsigned long) ; 
 int clamp (int,int,int) ; 

__attribute__((used)) static int sclk_div_getdiv(struct clk_hw *hw, unsigned long rate,
			   unsigned long prate, int maxdiv)
{
	int div = DIV_ROUND_CLOSEST_ULL((u64)prate, rate);

	return clamp(div, 2, maxdiv);
}