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
typedef  struct stm_fs const stm_fs ;
struct st_clk_quadfs_fsynth {TYPE_1__* data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* get_rate ) (unsigned long,struct stm_fs const*,unsigned long*) ;int (* get_params ) (unsigned long,unsigned long,struct stm_fs const*) ;} ;

/* Variables and functions */
 struct st_clk_quadfs_fsynth* to_quadfs_fsynth (struct clk_hw*) ; 

__attribute__((used)) static long quadfs_find_best_rate(struct clk_hw *hw, unsigned long drate,
				unsigned long prate, struct stm_fs *params)
{
	struct st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	int (*clk_fs_get_rate)(unsigned long ,
				const struct stm_fs *, unsigned long *);
	int (*clk_fs_get_params)(unsigned long, unsigned long, struct stm_fs *);
	unsigned long rate = 0;

	clk_fs_get_rate = fs->data->get_rate;
	clk_fs_get_params = fs->data->get_params;

	if (!clk_fs_get_params(prate, drate, params))
		clk_fs_get_rate(prate, params, &rate);

	return rate;
}