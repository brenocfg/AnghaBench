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
struct fst_iface {int dummy; } ;
struct fst_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  foreach_fst_ctrl_call (int /*<<< orphan*/ ,struct fst_iface*) ; 
 int /*<<< orphan*/  fst_group_delete_if_empty (struct fst_group*) ; 
 int /*<<< orphan*/  fst_group_detach_iface (struct fst_group*,struct fst_iface*) ; 
 int /*<<< orphan*/  fst_group_get_id (struct fst_group*) ; 
 int /*<<< orphan*/  fst_group_update_ie (struct fst_group*) ; 
 int /*<<< orphan*/  fst_iface_delete (struct fst_iface*) ; 
 struct fst_group* fst_iface_get_group (struct fst_iface*) ; 
 int /*<<< orphan*/  fst_printf_iface (struct fst_iface*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_session_global_on_iface_detached (struct fst_iface*) ; 
 int /*<<< orphan*/  on_iface_removed ; 

void fst_detach(struct fst_iface *iface)
{
	struct fst_group *group = fst_iface_get_group(iface);

	fst_printf_iface(iface, MSG_DEBUG, "iface detached from group %s",
			 fst_group_get_id(group));
	fst_session_global_on_iface_detached(iface);
	foreach_fst_ctrl_call(on_iface_removed, iface);
	fst_group_detach_iface(group, iface);
	fst_iface_delete(iface);
	fst_group_update_ie(group);
	fst_group_delete_if_empty(group);
}