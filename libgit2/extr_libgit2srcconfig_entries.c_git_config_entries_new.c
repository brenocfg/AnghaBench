#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_config_entries ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int git_strmap_new (int /*<<< orphan*/ *) ; 

int git_config_entries_new(git_config_entries **out)
{
	git_config_entries *entries;
	int error;

	entries = git__calloc(1, sizeof(git_config_entries));
	GIT_ERROR_CHECK_ALLOC(entries);
	GIT_REFCOUNT_INC(entries);

	if ((error = git_strmap_new(&entries->map)) < 0)
		git__free(entries);
	else
		*out = entries;

	return error;
}