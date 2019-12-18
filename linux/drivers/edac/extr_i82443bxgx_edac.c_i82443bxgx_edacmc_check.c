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
struct mem_ctl_info {int /*<<< orphan*/  mc_idx; } ;
struct i82443bxgx_edacmc_error_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i82443bxgx_edacmc_get_error_info (struct mem_ctl_info*,struct i82443bxgx_edacmc_error_info*) ; 
 int /*<<< orphan*/  i82443bxgx_edacmc_process_error_info (struct mem_ctl_info*,struct i82443bxgx_edacmc_error_info*,int) ; 

__attribute__((used)) static void i82443bxgx_edacmc_check(struct mem_ctl_info *mci)
{
	struct i82443bxgx_edacmc_error_info info;

	edac_dbg(1, "MC%d\n", mci->mc_idx);
	i82443bxgx_edacmc_get_error_info(mci, &info);
	i82443bxgx_edacmc_process_error_info(mci, &info, 1);
}