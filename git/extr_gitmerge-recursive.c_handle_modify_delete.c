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
struct object_id {int dummy; } ;
struct merge_options {char* branch1; char* branch2; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int handle_change_delete (struct merge_options*,char const*,int /*<<< orphan*/ *,struct object_id*,int,struct object_id*,int,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_modify_delete(struct merge_options *o,
				const char *path,
				struct object_id *o_oid, int o_mode,
				struct object_id *a_oid, int a_mode,
				struct object_id *b_oid, int b_mode)
{
	const char *modify_branch, *delete_branch;
	struct object_id *changed_oid;
	int changed_mode;

	if (a_oid) {
		modify_branch = o->branch1;
		delete_branch = o->branch2;
		changed_oid = a_oid;
		changed_mode = a_mode;
	} else {
		modify_branch = o->branch2;
		delete_branch = o->branch1;
		changed_oid = b_oid;
		changed_mode = b_mode;
	}

	return handle_change_delete(o,
				    path, NULL,
				    o_oid, o_mode,
				    changed_oid, changed_mode,
				    modify_branch, delete_branch,
				    _("modify"), _("modified"));
}