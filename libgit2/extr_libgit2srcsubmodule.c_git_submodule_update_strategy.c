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
typedef  scalar_t__ git_submodule_update_t ;
struct TYPE_4__ {scalar_t__ update; } ;
typedef  TYPE_1__ git_submodule ;

/* Variables and functions */
 scalar_t__ GIT_SUBMODULE_UPDATE_CHECKOUT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

git_submodule_update_t git_submodule_update_strategy(git_submodule *submodule)
{
	assert(submodule);
	return (submodule->update < GIT_SUBMODULE_UPDATE_CHECKOUT) ?
		GIT_SUBMODULE_UPDATE_CHECKOUT : submodule->update;
}