#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_rebase_operation ;
struct TYPE_4__ {int /*<<< orphan*/  operations; } ;
typedef  TYPE_1__ git_rebase ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * git_array_get (int /*<<< orphan*/ ,size_t) ; 

git_rebase_operation *git_rebase_operation_byindex(git_rebase *rebase, size_t idx)
{
	assert(rebase);

	return git_array_get(rebase->operations, idx);
}