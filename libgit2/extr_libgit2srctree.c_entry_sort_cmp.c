#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  filename_len; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ git_tree_entry ;

/* Variables and functions */
 int /*<<< orphan*/  git__strncmp ; 
 int git_path_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry__is_tree (TYPE_1__ const*) ; 

__attribute__((used)) static int entry_sort_cmp(const void *a, const void *b)
{
	const git_tree_entry *e1 = (const git_tree_entry *)a;
	const git_tree_entry *e2 = (const git_tree_entry *)b;

	return git_path_cmp(
		e1->filename, e1->filename_len, git_tree_entry__is_tree(e1),
		e2->filename, e2->filename_len, git_tree_entry__is_tree(e2),
		git__strncmp);
}