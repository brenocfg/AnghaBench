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
 int git_configset_get_string_const (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  git_die_config (char const*,int /*<<< orphan*/ *) ; 

int repo_config_get_string_const(struct repository *repo,
				 const char *key, const char **dest)
{
	int ret;
	git_config_check_init(repo);
	ret = git_configset_get_string_const(repo->config, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}