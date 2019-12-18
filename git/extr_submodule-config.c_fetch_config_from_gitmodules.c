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
struct fetch_config {int* max_children; int* recurse_submodules; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_from_gitmodules (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fetch_config*) ; 
 int /*<<< orphan*/  gitmodules_fetch_config ; 
 int /*<<< orphan*/  the_repository ; 

void fetch_config_from_gitmodules(int *max_children, int *recurse_submodules)
{
	struct fetch_config config = {
		.max_children = max_children,
		.recurse_submodules = recurse_submodules
	};
	config_from_gitmodules(gitmodules_fetch_config, the_repository, &config);
}