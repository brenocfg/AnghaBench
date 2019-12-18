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
struct iter_donotq {int /*<<< orphan*/  tree; int /*<<< orphan*/  region; } ;
struct config_file {scalar_t__ do_ip6; scalar_t__ donotquery_localhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  donotq_str_cfg (struct iter_donotq*,char*) ; 
 int /*<<< orphan*/  read_donotq (struct iter_donotq*,struct config_file*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 

int 
donotq_apply_cfg(struct iter_donotq* dq, struct config_file* cfg)
{
	regional_free_all(dq->region);
	addr_tree_init(&dq->tree);
	if(!read_donotq(dq, cfg))
		return 0;
	if(cfg->donotquery_localhost) {
		if(!donotq_str_cfg(dq, "127.0.0.0/8"))
			return 0;
		if(cfg->do_ip6) {
			if(!donotq_str_cfg(dq, "::1"))
				return 0;
		}
	}
	addr_tree_init_parents(&dq->tree);
	return 1;
}