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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct clk_rcg_dfs_data {struct clk_init_data* init; struct clk_rcg2* rcg; } ;
struct clk_rcg2 {int /*<<< orphan*/ * freq_tbl; scalar_t__ cmd_rcgr; } ;
struct clk_init_data {int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_GET_RATE_NOCACHE ; 
 int EINVAL ; 
 scalar_t__ SE_CMD_DFSR_OFFSET ; 
 int SE_CMD_DFS_EN ; 
 int /*<<< orphan*/  clk_rcg2_dfs_ops ; 
 int regmap_read (struct regmap*,scalar_t__,int*) ; 

__attribute__((used)) static int clk_rcg2_enable_dfs(const struct clk_rcg_dfs_data *data,
			       struct regmap *regmap)
{
	struct clk_rcg2 *rcg = data->rcg;
	struct clk_init_data *init = data->init;
	u32 val;
	int ret;

	ret = regmap_read(regmap, rcg->cmd_rcgr + SE_CMD_DFSR_OFFSET, &val);
	if (ret)
		return -EINVAL;

	if (!(val & SE_CMD_DFS_EN))
		return 0;

	/*
	 * Rate changes with consumer writing a register in
	 * their own I/O region
	 */
	init->flags |= CLK_GET_RATE_NOCACHE;
	init->ops = &clk_rcg2_dfs_ops;

	rcg->freq_tbl = NULL;

	return 0;
}