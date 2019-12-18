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
 int /*<<< orphan*/  EVIL_SM_NAME ; 
 int /*<<< orphan*/  EVIL_SM_NAME_WINDOWS_UNESC ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int find_evil(git_submodule *sm, const char *name, void *payload)
{
	int *foundit = (int *) payload;

	GIT_UNUSED(sm);

	if (!git__strcmp(EVIL_SM_NAME, name) ||
	    !git__strcmp(EVIL_SM_NAME_WINDOWS_UNESC, name))
		*foundit = true;

	return 0;
}