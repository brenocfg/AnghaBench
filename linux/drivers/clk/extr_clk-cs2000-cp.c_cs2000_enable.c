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
struct cs2000_priv {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int cs2000_clk_out_enable (struct cs2000_priv*,int) ; 
 int cs2000_enable_dev_config (struct cs2000_priv*,int) ; 
 int cs2000_wait_pll_lock (struct cs2000_priv*) ; 
 struct cs2000_priv* hw_to_priv (struct clk_hw*) ; 

__attribute__((used)) static int cs2000_enable(struct clk_hw *hw)
{
	struct cs2000_priv *priv = hw_to_priv(hw);
	int ret;

	ret = cs2000_enable_dev_config(priv, true);
	if (ret < 0)
		return ret;

	ret = cs2000_clk_out_enable(priv, true);
	if (ret < 0)
		return ret;

	ret = cs2000_wait_pll_lock(priv);
	if (ret < 0)
		return ret;

	return ret;
}