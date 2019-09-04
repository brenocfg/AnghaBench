#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; int /*<<< orphan*/  entry_path; int /*<<< orphan*/  entry_pool; TYPE_4__ frames; } ;
typedef  TYPE_1__ tree_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  git_array_clear (TYPE_4__) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterator_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_iterator_frame_pop (TYPE_1__*) ; 

__attribute__((used)) static void tree_iterator_clear(tree_iterator *iter)
{
	while (iter->frames.size)
		tree_iterator_frame_pop(iter);

	git_array_clear(iter->frames);

	git_pool_clear(&iter->entry_pool);
	git_buf_clear(&iter->entry_path);

	iterator_clear(&iter->base);
}