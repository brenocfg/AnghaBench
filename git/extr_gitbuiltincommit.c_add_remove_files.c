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
struct string_list_item {int /*<<< orphan*/  string; scalar_t__ util; } ;
struct string_list {int nr; struct string_list_item* items; } ;
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_to_cache (int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  remove_file_from_cache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_remove_files(struct string_list *list)
{
	int i;
	for (i = 0; i < list->nr; i++) {
		struct stat st;
		struct string_list_item *p = &(list->items[i]);

		/* p->util is skip-worktree */
		if (p->util)
			continue;

		if (!lstat(p->string, &st)) {
			if (add_to_cache(p->string, &st, 0))
				die(_("updating files failed"));
		} else
			remove_file_from_cache(p->string);
	}
}