#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int git_submodule_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sync_one_submodule(
	git_submodule *sm, const char *name, void *payload)
{
	GIT_UNUSED(name);
	GIT_UNUSED(payload);
	return git_submodule_sync(sm);
}