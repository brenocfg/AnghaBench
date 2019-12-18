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
struct TYPE_3__ {int /*<<< orphan*/  entry_path; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ tree_iterator ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_iterator_clear (TYPE_1__*) ; 

__attribute__((used)) static void tree_iterator_free(git_iterator *i)
{
	tree_iterator *iter = (tree_iterator *)i;

	tree_iterator_clear(iter);

	git_tree_free(iter->root);
	git_buf_dispose(&iter->entry_path);
}