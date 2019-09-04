#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_rebase_operation ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ inmemory; } ;
typedef  TYPE_1__ git_rebase ;

/* Variables and functions */
 scalar_t__ GIT_REBASE_TYPE_MERGE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int rebase_movenext (TYPE_1__*) ; 
 int rebase_next_inmemory (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int rebase_next_merge (int /*<<< orphan*/ **,TYPE_1__*) ; 

int git_rebase_next(
	git_rebase_operation **out,
	git_rebase *rebase)
{
	int error;

	assert(out && rebase);

	if ((error = rebase_movenext(rebase)) < 0)
		return error;

	if (rebase->inmemory)
		error = rebase_next_inmemory(out, rebase);
	else if (rebase->type == GIT_REBASE_TYPE_MERGE)
		error = rebase_next_merge(out, rebase);
	else
		abort();

	return error;
}