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

/* Variables and functions */
 int /*<<< orphan*/  config_from_gitmodules (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  gitmodules_update_clone_config ; 
 int /*<<< orphan*/  the_repository ; 

void update_clone_config_from_gitmodules(int *max_jobs)
{
	config_from_gitmodules(gitmodules_update_clone_config, the_repository, &max_jobs);
}