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
struct TYPE_4__ {char* value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GET_ALL_ERRORS ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int get_entry (TYPE_1__**,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_readonly (int /*<<< orphan*/  const*) ; 

int git_config_get_string(
	const char **out, const git_config *cfg, const char *name)
{
	git_config_entry *entry;
	int ret;

	if (!is_readonly(cfg)) {
		git_error_set(GIT_ERROR_CONFIG, "get_string called on a live config object");
		return -1;
	}

	ret = get_entry(&entry, cfg, name, true, GET_ALL_ERRORS);
	*out = !ret ? (entry->value ? entry->value : "") : NULL;

	git_config_entry_free(entry);

	return ret;
}