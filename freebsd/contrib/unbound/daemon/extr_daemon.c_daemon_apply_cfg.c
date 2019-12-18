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
struct daemon {TYPE_1__* env; int /*<<< orphan*/  superalloc; struct config_file* cfg; } ;
struct config_file {int /*<<< orphan*/  msg_cache_size; int /*<<< orphan*/  msg_cache_slabs; } ;
struct TYPE_2__ {int /*<<< orphan*/  infra_cache; int /*<<< orphan*/  rrset_cache; int /*<<< orphan*/  msg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_DEFAULT_STARTARRAY ; 
 int /*<<< orphan*/  config_apply (struct config_file*) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  infra_adjust (int /*<<< orphan*/ ,struct config_file*) ; 
 int /*<<< orphan*/  msgreply_sizefunc ; 
 int /*<<< orphan*/  query_entry_delete ; 
 int /*<<< orphan*/  query_info_compare ; 
 int /*<<< orphan*/  reply_info_delete ; 
 int /*<<< orphan*/  rrset_cache_adjust (int /*<<< orphan*/ ,struct config_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabhash_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabhash_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_is_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void daemon_apply_cfg(struct daemon* daemon, struct config_file* cfg)
{
        daemon->cfg = cfg;
	config_apply(cfg);
	if(!slabhash_is_size(daemon->env->msg_cache, cfg->msg_cache_size,
	   	cfg->msg_cache_slabs)) {
		slabhash_delete(daemon->env->msg_cache);
		daemon->env->msg_cache = slabhash_create(cfg->msg_cache_slabs,
			HASH_DEFAULT_STARTARRAY, cfg->msg_cache_size,
			msgreply_sizefunc, query_info_compare,
			query_entry_delete, reply_info_delete, NULL);
		if(!daemon->env->msg_cache) {
			fatal_exit("malloc failure updating config settings");
		}
	}
	if((daemon->env->rrset_cache = rrset_cache_adjust(
		daemon->env->rrset_cache, cfg, &daemon->superalloc)) == 0)
		fatal_exit("malloc failure updating config settings");
	if((daemon->env->infra_cache = infra_adjust(daemon->env->infra_cache,
		cfg))==0)
		fatal_exit("malloc failure updating config settings");
}