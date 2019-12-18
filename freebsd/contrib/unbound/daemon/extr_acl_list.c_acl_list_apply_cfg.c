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
struct views {int dummy; } ;
struct config_file {scalar_t__ do_ip6; } ;
struct acl_list {int /*<<< orphan*/  tree; int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  acl_list_str_cfg (struct acl_list*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_acl_list (struct acl_list*,struct config_file*) ; 
 int /*<<< orphan*/  read_acl_tag_actions (struct acl_list*,struct config_file*) ; 
 int /*<<< orphan*/  read_acl_tag_datas (struct acl_list*,struct config_file*) ; 
 int /*<<< orphan*/  read_acl_tags (struct acl_list*,struct config_file*) ; 
 int /*<<< orphan*/  read_acl_view (struct acl_list*,struct config_file*,struct views*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 

int 
acl_list_apply_cfg(struct acl_list* acl, struct config_file* cfg,
	struct views* v)
{
	regional_free_all(acl->region);
	addr_tree_init(&acl->tree);
	if(!read_acl_list(acl, cfg))
		return 0;
	if(!read_acl_view(acl, cfg, v))
		return 0;
	if(!read_acl_tags(acl, cfg))
		return 0;
	if(!read_acl_tag_actions(acl, cfg))
		return 0;
	if(!read_acl_tag_datas(acl, cfg))
		return 0;
	/* insert defaults, with '0' to ignore them if they are duplicates */
	if(!acl_list_str_cfg(acl, "0.0.0.0/0", "refuse", 0))
		return 0;
	if(!acl_list_str_cfg(acl, "127.0.0.0/8", "allow", 0))
		return 0;
	if(cfg->do_ip6) {
		if(!acl_list_str_cfg(acl, "::0/0", "refuse", 0))
			return 0;
		if(!acl_list_str_cfg(acl, "::1", "allow", 0))
			return 0;
		if(!acl_list_str_cfg(acl, "::ffff:127.0.0.1", "allow", 0))
			return 0;
	}
	addr_tree_init_parents(&acl->tree);
	return 1;
}