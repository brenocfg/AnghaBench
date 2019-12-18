#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tag {struct tag* next_tag; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tree; TYPE_1__* versions; } ;
struct branch {int /*<<< orphan*/  name; scalar_t__ delete; TYPE_2__ branch_tree; int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 TYPE_3__ command_buf ; 
 struct tag* first_tag ; 
 struct tag* last_tag ; 
 struct branch* lookup_branch (char const*) ; 
 struct branch* new_branch (char const*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_from (struct branch*) ; 
 int /*<<< orphan*/  read_next_command () ; 
 int /*<<< orphan*/  release_tree_content_recursive (int /*<<< orphan*/ *) ; 
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int unread_command_buf ; 

__attribute__((used)) static void parse_reset_branch(const char *arg)
{
	struct branch *b;
	const char *tag_name;

	b = lookup_branch(arg);
	if (b) {
		oidclr(&b->oid);
		oidclr(&b->branch_tree.versions[0].oid);
		oidclr(&b->branch_tree.versions[1].oid);
		if (b->branch_tree.tree) {
			release_tree_content_recursive(b->branch_tree.tree);
			b->branch_tree.tree = NULL;
		}
	}
	else
		b = new_branch(arg);
	read_next_command();
	parse_from(b);
	if (b->delete && skip_prefix(b->name, "refs/tags/", &tag_name)) {
		/*
		 * Elsewhere, we call dump_branches() before dump_tags(),
		 * and dump_branches() will handle ref deletions first, so
		 * in order to make sure the deletion actually takes effect,
		 * we need to remove the tag from our list of tags to update.
		 *
		 * NEEDSWORK: replace list of tags with hashmap for faster
		 * deletion?
		 */
		struct tag *t, *prev = NULL;
		for (t = first_tag; t; t = t->next_tag) {
			if (!strcmp(t->name, tag_name))
				break;
			prev = t;
		}
		if (t) {
			if (prev)
				prev->next_tag = t->next_tag;
			else
				first_tag = t->next_tag;
			if (!t->next_tag)
				last_tag = prev;
			/* There is no mem_pool_free(t) function to call. */
		}
	}
	if (command_buf.len > 0)
		unread_command_buf = 1;
}