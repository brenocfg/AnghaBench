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
struct object {int dummy; } ;
struct fsck_options {int (* walk ) (struct object*,int /*<<< orphan*/ ,void*,struct fsck_options*) ;} ;
struct commit_list {struct commit_list* next; TYPE_1__* item; } ;
struct commit {struct commit_list* parents; int /*<<< orphan*/  object; } ;
struct TYPE_4__ {struct object object; } ;
struct TYPE_3__ {struct object object; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_COMMIT ; 
 int /*<<< orphan*/  OBJ_TREE ; 
 TYPE_2__* get_commit_tree (struct commit*) ; 
 char* get_object_name (struct fsck_options*,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  put_object_name (struct fsck_options*,struct object*,char*,...) ; 
 int strlen (char const*) ; 
 int stub1 (struct object*,int /*<<< orphan*/ ,void*,struct fsck_options*) ; 
 int stub2 (struct object*,int /*<<< orphan*/ ,void*,struct fsck_options*) ; 

__attribute__((used)) static int fsck_walk_commit(struct commit *commit, void *data, struct fsck_options *options)
{
	int counter = 0, generation = 0, name_prefix_len = 0;
	struct commit_list *parents;
	int res;
	int result;
	const char *name;

	if (parse_commit(commit))
		return -1;

	name = get_object_name(options, &commit->object);
	if (name)
		put_object_name(options, &get_commit_tree(commit)->object,
				"%s:", name);

	result = options->walk((struct object *)get_commit_tree(commit),
			       OBJ_TREE, data, options);
	if (result < 0)
		return result;
	res = result;

	parents = commit->parents;
	if (name && parents) {
		int len = strlen(name), power;

		if (len && name[len - 1] == '^') {
			generation = 1;
			name_prefix_len = len - 1;
		}
		else { /* parse ~<generation> suffix */
			for (generation = 0, power = 1;
			     len && isdigit(name[len - 1]);
			     power *= 10)
				generation += power * (name[--len] - '0');
			if (power > 1 && len && name[len - 1] == '~')
				name_prefix_len = len - 1;
		}
	}

	while (parents) {
		if (name) {
			struct object *obj = &parents->item->object;

			if (counter++)
				put_object_name(options, obj, "%s^%d",
					name, counter);
			else if (generation > 0)
				put_object_name(options, obj, "%.*s~%d",
					name_prefix_len, name, generation + 1);
			else
				put_object_name(options, obj, "%s^", name);
		}
		result = options->walk((struct object *)parents->item, OBJ_COMMIT, data, options);
		if (result < 0)
			return result;
		if (!res)
			res = result;
		parents = parents->next;
	}
	return res;
}