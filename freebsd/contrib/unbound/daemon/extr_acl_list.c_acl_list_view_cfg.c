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
struct views {int dummy; } ;
struct acl_list {int dummy; } ;
struct acl_addr {TYPE_1__* view; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct acl_addr* acl_find_or_create (struct acl_list*,char const*) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 TYPE_1__* views_find_view (struct views*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acl_list_view_cfg(struct acl_list* acl, const char* str, const char* str2,
	struct views* vs)
{
	struct acl_addr* node;
	if(!(node=acl_find_or_create(acl, str)))
		return 0;
	node->view = views_find_view(vs, str2, 0 /* get read lock*/);
	if(!node->view) {
		log_err("no view with name: %s", str2);
		return 0;
	}
	lock_rw_unlock(&node->view->lock);
	return 1;
}