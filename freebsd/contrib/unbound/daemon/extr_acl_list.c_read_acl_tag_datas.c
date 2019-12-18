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
struct config_str3list {struct config_str3list* str3; struct config_str3list* str2; struct config_str3list* str; struct config_str3list* next; } ;
struct config_file {struct config_str3list* acl_tag_datas; } ;
struct acl_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acl_list_tag_data_cfg (struct acl_list*,struct config_file*,struct config_str3list*,struct config_str3list*,struct config_str3list*) ; 
 int /*<<< orphan*/  config_deltrplstrlist (struct config_str3list*) ; 
 int /*<<< orphan*/  free (struct config_str3list*) ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static int 
read_acl_tag_datas(struct acl_list* acl, struct config_file* cfg)
{
	struct config_str3list* p, *np;
	p = cfg->acl_tag_datas;
	cfg->acl_tag_datas = NULL;
	while(p) {
		log_assert(p->str && p->str2 && p->str3);
		if(!acl_list_tag_data_cfg(acl, cfg, p->str, p->str2, p->str3)) {
			config_deltrplstrlist(p);
			return 0;
		}
		/* free the items as we go to free up memory */
		np = p->next;
		free(p->str);
		free(p->str2);
		free(p->str3);
		free(p);
		p = np;
	}
	return 1;
}