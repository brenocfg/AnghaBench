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
struct iter_hints {int /*<<< orphan*/  tree; } ;
struct delegpt {int dummy; } ;
struct config_file {int /*<<< orphan*/  do_ip6; int /*<<< orphan*/  do_ip4; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 struct delegpt* compile_time_root_prime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hints_del_tree (struct iter_hints*) ; 
 int /*<<< orphan*/  hints_insert (struct iter_hints*,int /*<<< orphan*/ ,struct delegpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hints_lookup_root (struct iter_hints*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_root_hints_list (struct iter_hints*,struct config_file*) ; 
 int /*<<< orphan*/  read_stubs (struct iter_hints*,struct config_file*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

int 
hints_apply_cfg(struct iter_hints* hints, struct config_file* cfg)
{
	hints_del_tree(hints);
	name_tree_init(&hints->tree);
	
	/* read root hints */
	if(!read_root_hints_list(hints, cfg))
		return 0;

	/* read stub hints */
	if(!read_stubs(hints, cfg))
		return 0;

	/* use fallback compiletime root hints */
	if(!hints_lookup_root(hints, LDNS_RR_CLASS_IN)) {
		struct delegpt* dp = compile_time_root_prime(cfg->do_ip4,
			cfg->do_ip6);
		verbose(VERB_ALGO, "no config, using builtin root hints.");
		if(!dp) 
			return 0;
		if(!hints_insert(hints, LDNS_RR_CLASS_IN, dp, 0))
			return 0;
	}

	name_tree_init_parents(&hints->tree);
	return 1;
}