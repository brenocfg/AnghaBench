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
struct string_list {int dummy; } ;
struct repository {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_check_init (struct repository*) ; 
 struct string_list const* git_configset_get_value_multi (int /*<<< orphan*/ ,char const*) ; 

const struct string_list *repo_config_get_value_multi(struct repository *repo,
						      const char *key)
{
	git_config_check_init(repo);
	return git_configset_get_value_multi(repo->config, key);
}