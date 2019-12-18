#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_rebase_operation_t ;
struct TYPE_6__ {char const* exec; int /*<<< orphan*/  id; scalar_t__ type; } ;
typedef  TYPE_1__ git_rebase_operation ;
struct TYPE_7__ {int /*<<< orphan*/  operations; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_REBASE_OPERATION_EXEC ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static git_rebase_operation *rebase_operation_alloc(
	git_rebase *rebase,
	git_rebase_operation_t type,
	git_oid *id,
	const char *exec)
{
	git_rebase_operation *operation;

	assert((type == GIT_REBASE_OPERATION_EXEC) == !id);
	assert((type == GIT_REBASE_OPERATION_EXEC) == !!exec);

	if ((operation = git_array_alloc(rebase->operations)) == NULL)
		return NULL;

	operation->type = type;
	git_oid_cpy((git_oid *)&operation->id, id);
	operation->exec = exec;

	return operation;
}