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
struct fst_session {int dummy; } ;
struct fst_group {int /*<<< orphan*/  ifaces; int /*<<< orphan*/  global_groups_lentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foreach_fst_ctrl_call (int /*<<< orphan*/ ,struct fst_group*) ; 
 int /*<<< orphan*/  fst_printf_group (struct fst_group*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fst_session_delete (struct fst_session*) ; 
 struct fst_session* fst_session_global_get_first_by_group (struct fst_group*) ; 
 int /*<<< orphan*/  on_group_deleted ; 
 int /*<<< orphan*/  os_free (struct fst_group*) ; 

void fst_group_delete(struct fst_group *group)
{
	struct fst_session *s;

	dl_list_del(&group->global_groups_lentry);
	WPA_ASSERT(dl_list_empty(&group->ifaces));
	foreach_fst_ctrl_call(on_group_deleted, group);
	fst_printf_group(group, MSG_DEBUG, "instance deleted");
	while ((s = fst_session_global_get_first_by_group(group)) != NULL)
		fst_session_delete(s);
	os_free(group);
}