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
struct config_str2list {scalar_t__ str2; scalar_t__ str; struct config_str2list* next; } ;
struct config_file {struct config_str2list* acls; } ;
struct acl_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acl_list_str_cfg (struct acl_list*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static int 
read_acl_list(struct acl_list* acl, struct config_file* cfg)
{
	struct config_str2list* p;
	for(p = cfg->acls; p; p = p->next) {
		log_assert(p->str && p->str2);
		if(!acl_list_str_cfg(acl, p->str, p->str2, 1))
			return 0;
	}
	return 1;
}