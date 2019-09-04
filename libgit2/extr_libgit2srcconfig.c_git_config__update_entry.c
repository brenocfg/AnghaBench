#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int git_config__lookup_entry (TYPE_1__**,int /*<<< orphan*/ *,char const*,int) ; 
 int git_config_delete_entry (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int git_config_set_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

int git_config__update_entry(
	git_config *config,
	const char *key,
	const char *value,
	bool overwrite_existing,
	bool only_if_existing)
{
	int error = 0;
	git_config_entry *ce = NULL;

	if ((error = git_config__lookup_entry(&ce, config, key, false)) < 0)
		return error;

	if (!ce && only_if_existing) /* entry doesn't exist */
		return 0;
	if (ce && !overwrite_existing) /* entry would be overwritten */
		return 0;
	if (value && ce && ce->value && !strcmp(ce->value, value)) /* no change */
		return 0;
	if (!value && (!ce || !ce->value)) /* asked to delete absent entry */
		return 0;

	if (!value)
		error = git_config_delete_entry(config, key);
	else
		error = git_config_set_string(config, key, value);

	git_config_entry_free(ce);
	return error;
}