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
typedef  scalar_t__ git_submodule_ignore_t ;
struct TYPE_4__ {scalar_t__ ignore; } ;
typedef  TYPE_1__ git_submodule ;

/* Variables and functions */
 scalar_t__ GIT_SUBMODULE_IGNORE_NONE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

git_submodule_ignore_t git_submodule_ignore(git_submodule *submodule)
{
	assert(submodule);
	return (submodule->ignore < GIT_SUBMODULE_IGNORE_NONE) ?
		GIT_SUBMODULE_IGNORE_NONE : submodule->ignore;
}