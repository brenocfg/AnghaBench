#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct repository {TYPE_1__* objects; } ;
struct prepare_pack_data {int local; struct string_list* garbage; struct repository* r; TYPE_2__* m; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  object_dir; } ;
struct TYPE_3__ {TYPE_2__* multi_pack_index; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  for_each_file_in_pack_dir (char*,int /*<<< orphan*/ ,struct prepare_pack_data*) ; 
 int /*<<< orphan*/  prepare_pack ; 
 int /*<<< orphan*/  report_pack_garbage (struct string_list*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_packed_git_one(struct repository *r, char *objdir, int local)
{
	struct prepare_pack_data data;
	struct string_list garbage = STRING_LIST_INIT_DUP;

	data.m = r->objects->multi_pack_index;

	/* look for the multi-pack-index for this object directory */
	while (data.m && strcmp(data.m->object_dir, objdir))
		data.m = data.m->next;

	data.r = r;
	data.garbage = &garbage;
	data.local = local;

	for_each_file_in_pack_dir(objdir, prepare_pack, &data);

	report_pack_garbage(data.garbage);
	string_list_clear(data.garbage, 0);
}