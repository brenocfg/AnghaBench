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
struct TYPE_3__ {int /*<<< orphan*/ * diff_drivers; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_diff_driver_registry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REPOSITORY ; 
 int /*<<< orphan*/ * git__compare_and_swap (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_driver_registry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_diff_driver_registry_new () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static git_diff_driver_registry *git_repository_driver_registry(
	git_repository *repo)
{
	if (!repo->diff_drivers) {
		git_diff_driver_registry *reg = git_diff_driver_registry_new();
		reg = git__compare_and_swap(&repo->diff_drivers, NULL, reg);

		if (reg != NULL) /* if we race, free losing allocation */
			git_diff_driver_registry_free(reg);
	}

	if (!repo->diff_drivers)
		git_error_set(GIT_ERROR_REPOSITORY, "unable to create diff driver registry");

	return repo->diff_drivers;
}