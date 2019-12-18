#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* tree_entry; int /*<<< orphan*/  parent_path; } ;
typedef  TYPE_1__ tree_iterator_entry ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_5__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_tree_entry__is_tree (TYPE_3__*) ; 

__attribute__((used)) static int tree_iterator_compute_path(
	git_buf *out,
	tree_iterator_entry *entry)
{
	git_buf_clear(out);

	if (entry->parent_path)
		git_buf_joinpath(out, entry->parent_path, entry->tree_entry->filename);
	else
		git_buf_puts(out, entry->tree_entry->filename);

	if (git_tree_entry__is_tree(entry->tree_entry))
		git_buf_putc(out, '/');

	if (git_buf_oom(out))
		return -1;

	return 0;
}