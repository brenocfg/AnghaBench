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
struct clk_lookup {struct clk_hw* clk_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct clk_lookup* clk_find (char const*,char const*) ; 
 int /*<<< orphan*/  clocks_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct clk_hw *clk_find_hw(const char *dev_id, const char *con_id)
{
	struct clk_lookup *cl;
	struct clk_hw *hw = ERR_PTR(-ENOENT);

	mutex_lock(&clocks_mutex);
	cl = clk_find(dev_id, con_id);
	if (cl)
		hw = cl->clk_hw;
	mutex_unlock(&clocks_mutex);

	return hw;
}