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
struct TYPE_4__ {size_t current; scalar_t__ started; } ;
typedef  TYPE_1__ git_rebase ;

/* Variables and functions */
 size_t GIT_REBASE_NO_OPERATION ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

size_t git_rebase_operation_current(git_rebase *rebase)
{
	assert(rebase);

	return rebase->started ? rebase->current : GIT_REBASE_NO_OPERATION;
}