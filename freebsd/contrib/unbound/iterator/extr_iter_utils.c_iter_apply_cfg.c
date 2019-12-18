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
struct iter_env {int max_dependency_depth; int /*<<< orphan*/  supports_ipv4; int /*<<< orphan*/  supports_ipv6; scalar_t__ caps_white; scalar_t__ priv; scalar_t__ donotq; int /*<<< orphan*/ * target_fetch_policy; } ;
struct config_file {int /*<<< orphan*/  do_ip4; int /*<<< orphan*/  do_ip6; scalar_t__ caps_whitelist; int /*<<< orphan*/  target_fetch_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  caps_white_apply_cfg (scalar_t__,struct config_file*) ; 
 int /*<<< orphan*/  donotq_apply_cfg (scalar_t__,struct config_file*) ; 
 scalar_t__ donotq_create () ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  name_tree_compare ; 
 int /*<<< orphan*/  priv_apply_cfg (scalar_t__,struct config_file*) ; 
 scalar_t__ priv_create () ; 
 scalar_t__ rbtree_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_fetch_policy (struct iter_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int 
iter_apply_cfg(struct iter_env* iter_env, struct config_file* cfg)
{
	int i;
	/* target fetch policy */
	if(!read_fetch_policy(iter_env, cfg->target_fetch_policy))
		return 0;
	for(i=0; i<iter_env->max_dependency_depth+1; i++)
		verbose(VERB_QUERY, "target fetch policy for level %d is %d",
			i, iter_env->target_fetch_policy[i]);
	
	if(!iter_env->donotq)
		iter_env->donotq = donotq_create();
	if(!iter_env->donotq || !donotq_apply_cfg(iter_env->donotq, cfg)) {
		log_err("Could not set donotqueryaddresses");
		return 0;
	}
	if(!iter_env->priv)
		iter_env->priv = priv_create();
	if(!iter_env->priv || !priv_apply_cfg(iter_env->priv, cfg)) {
		log_err("Could not set private addresses");
		return 0;
	}
	if(cfg->caps_whitelist) {
		if(!iter_env->caps_white)
			iter_env->caps_white = rbtree_create(name_tree_compare);
		if(!iter_env->caps_white || !caps_white_apply_cfg(
			iter_env->caps_white, cfg)) {
			log_err("Could not set capsforid whitelist");
			return 0;
		}

	}
	iter_env->supports_ipv6 = cfg->do_ip6;
	iter_env->supports_ipv4 = cfg->do_ip4;
	return 1;
}