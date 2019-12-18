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
struct ixl_pf {int stat_offsets_loaded; int /*<<< orphan*/  stats_offsets; int /*<<< orphan*/  stats; } ;
struct i40e_hw_port_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

void
ixl_pf_reset_stats(struct ixl_pf *pf)
{
	bzero(&pf->stats, sizeof(struct i40e_hw_port_stats));
	bzero(&pf->stats_offsets, sizeof(struct i40e_hw_port_stats));
	pf->stat_offsets_loaded = false;
}