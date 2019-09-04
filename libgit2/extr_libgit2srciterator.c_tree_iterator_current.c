#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_1__* cb; } ;
struct TYPE_8__ {int /*<<< orphan*/  entry; TYPE_3__ frames; TYPE_2__ base; } ;
typedef  TYPE_4__ tree_iterator ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_5__ {int (* advance ) (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  iterator__has_been_accessed (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tree_iterator_current(
	const git_index_entry **out, git_iterator *i)
{
	tree_iterator *iter = (tree_iterator *)i;

	if (!iterator__has_been_accessed(i))
		return iter->base.cb->advance(out, i);

	if (!iter->frames.size) {
		*out = NULL;
		return GIT_ITEROVER;
	}

	*out = &iter->entry;
	return 0;
}