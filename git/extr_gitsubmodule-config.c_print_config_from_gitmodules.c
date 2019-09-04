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
 int CONFIG_INVALID_KEY ; 
 int /*<<< orphan*/  config_from_gitmodules (int /*<<< orphan*/ ,struct repository*,char*) ; 
 int /*<<< orphan*/  config_print_callback ; 
 int /*<<< orphan*/  free (char*) ; 
 int git_config_parse_key (char const*,char**,int /*<<< orphan*/ *) ; 

int print_config_from_gitmodules(struct repository *repo, const char *key)
{
	int ret;
	char *store_key;

	ret = git_config_parse_key(key, &store_key, NULL);
	if (ret < 0)
		return CONFIG_INVALID_KEY;

	config_from_gitmodules(config_print_callback, repo, store_key);

	free(store_key);
	return 0;
}