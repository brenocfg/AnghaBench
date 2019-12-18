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
struct table_info {scalar_t__ xstate; scalar_t__ state; } ;
struct radix_node_head {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct radix_node_head*) ;} ;
struct radix_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  flush_radix_entry ; 
 int /*<<< orphan*/  free (struct radix_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rn_detachhead (scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct radix_node_head*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct radix_node_head*) ; 

__attribute__((used)) static void
ta_destroy_radix(void *ta_state, struct table_info *ti)
{
	struct radix_cfg *cfg;
	struct radix_node_head *rnh;

	cfg = (struct radix_cfg *)ta_state;

	rnh = (struct radix_node_head *)(ti->state);
	rnh->rnh_walktree(&rnh->rh, flush_radix_entry, rnh);
	rn_detachhead(&ti->state);

	rnh = (struct radix_node_head *)(ti->xstate);
	rnh->rnh_walktree(&rnh->rh, flush_radix_entry, rnh);
	rn_detachhead(&ti->xstate);

	free(cfg, M_IPFW);
}