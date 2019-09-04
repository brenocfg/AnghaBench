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
struct delta_info {int /*<<< orphan*/  delta_off; } ;
struct TYPE_3__ {int /*<<< orphan*/  deltas; int /*<<< orphan*/  entry_start; } ;
typedef  TYPE_1__ git_indexer ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct delta_info*) ; 
 struct delta_info* git__calloc (int,int) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,struct delta_info*) ; 

__attribute__((used)) static int store_delta(git_indexer *idx)
{
	struct delta_info *delta;

	delta = git__calloc(1, sizeof(struct delta_info));
	GIT_ERROR_CHECK_ALLOC(delta);
	delta->delta_off = idx->entry_start;

	if (git_vector_insert(&idx->deltas, delta) < 0)
		return -1;

	return 0;
}