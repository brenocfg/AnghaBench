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
struct repository {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_check_init (struct repository*) ; 
 int repo_config_get_string_const (struct repository*,char const*,char const**) ; 

int repo_config_get_string(struct repository *repo,
			   const char *key, char **dest)
{
	git_config_check_init(repo);
	return repo_config_get_string_const(repo, key, (const char **)dest);
}