#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_indexwriter ;
struct TYPE_5__ {scalar_t__ dirty; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_INDEXWRITER_INIT ; 
 int /*<<< orphan*/  git_indexwriter_cleanup (int /*<<< orphan*/ *) ; 
 int git_indexwriter_commit (int /*<<< orphan*/ *) ; 
 int git_indexwriter_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  truncate_racily_clean (TYPE_1__*) ; 

int git_index_write(git_index *index)
{
	git_indexwriter writer = GIT_INDEXWRITER_INIT;
	int error;

	truncate_racily_clean(index);

	if ((error = git_indexwriter_init(&writer, index)) == 0 &&
		(error = git_indexwriter_commit(&writer)) == 0)
		index->dirty = 0;

	git_indexwriter_cleanup(&writer);

	return error;
}