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
struct repository {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_check_init (struct repository*) ; 
 int git_configset_get_int (int /*<<< orphan*/ ,char const*,int*) ; 

int repo_config_get_int(struct repository *repo,
			const char *key, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_int(repo->config, key, dest);
}