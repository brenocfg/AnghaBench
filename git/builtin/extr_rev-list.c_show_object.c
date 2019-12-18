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
struct rev_list_info {int flags; } ;
struct object {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int REV_LIST_QUIET ; 
 scalar_t__ arg_show_object_names ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ finish_object (struct object*,char const*,void*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  progress_counter ; 
 int /*<<< orphan*/  show_object_with_name (int /*<<< orphan*/ ,struct object*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_object(struct object *obj, const char *name, void *cb_data)
{
	struct rev_list_info *info = cb_data;
	if (finish_object(obj, name, cb_data))
		return;
	display_progress(progress, ++progress_counter);
	if (info->flags & REV_LIST_QUIET)
		return;
	if (arg_show_object_names)
		show_object_with_name(stdout, obj, name);
	else
		printf("%s\n", oid_to_hex(&obj->oid));
}