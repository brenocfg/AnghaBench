#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct freq_tbl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct clk_rcg2 {TYPE_1__ clkr; struct freq_tbl* freq_tbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_PERF_LEVEL ; 
 int /*<<< orphan*/  clk_rcg2_dfs_populate_freq (int /*<<< orphan*/ *,int,struct freq_tbl*) ; 
 struct freq_tbl* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_rcg2_dfs_populate_freq_table(struct clk_rcg2 *rcg)
{
	struct freq_tbl *freq_tbl;
	int i;

	/* Allocate space for 1 extra since table is NULL terminated */
	freq_tbl = kcalloc(MAX_PERF_LEVEL + 1, sizeof(*freq_tbl), GFP_KERNEL);
	if (!freq_tbl)
		return -ENOMEM;
	rcg->freq_tbl = freq_tbl;

	for (i = 0; i < MAX_PERF_LEVEL; i++)
		clk_rcg2_dfs_populate_freq(&rcg->clkr.hw, i, freq_tbl + i);

	return 0;
}