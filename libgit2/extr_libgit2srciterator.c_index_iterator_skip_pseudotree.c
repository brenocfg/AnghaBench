#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct TYPE_13__ {scalar_t__ (* strncomp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ length; TYPE_5__** contents; } ;
struct TYPE_11__ {scalar_t__ next_idx; int skip_tree; TYPE_2__ tree_buf; TYPE_6__ base; TYPE_1__ entries; TYPE_3__* entry; } ;
typedef  TYPE_4__ index_iterator ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_5__ git_index_entry ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterator__has_been_accessed (TYPE_6__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_iterator_skip_pseudotree(index_iterator *iter)
{
	assert(iterator__has_been_accessed(&iter->base));
	assert(S_ISDIR(iter->entry->mode));

	while (true) {
		const git_index_entry *next_entry = NULL;

		if (++iter->next_idx >= iter->entries.length)
			return GIT_ITEROVER;

		next_entry = iter->entries.contents[iter->next_idx];

		if (iter->base.strncomp(iter->tree_buf.ptr, next_entry->path,
			iter->tree_buf.size) != 0)
			break;
	}

	iter->skip_tree = false;
	return 0;
}