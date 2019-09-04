#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ regex_t ;
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config_entries ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_9__ {int /*<<< orphan*/  header; } ;
typedef  TYPE_2__ diskfile_backend ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int config_refresh (int /*<<< orphan*/ *) ; 
 int config_write (TYPE_2__*,char const*,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * diskfile_entries_take (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_config__normalize_name (char const*,char**) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ *) ; 
 int git_config_entries_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_error_set_regex (TYPE_1__*,int) ; 
 int p_regcomp (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (TYPE_1__*) ; 

__attribute__((used)) static int config_delete_multivar(git_config_backend *cfg, const char *name, const char *regexp)
{
	diskfile_backend *b = (diskfile_backend *)cfg;
	git_config_entries *entries = NULL;
	git_config_entry *entry = NULL;
	regex_t preg = { 0 };
	char *key = NULL;
	int result;

	if ((result = git_config__normalize_name(name, &key)) < 0)
		goto out;

	if ((entries = diskfile_entries_take(&b->header)) == NULL) {
		result = -1;
		goto out;
	}

	if ((result = git_config_entries_get(&entry, entries, key)) < 0) {
		if (result == GIT_ENOTFOUND)
			git_error_set(GIT_ERROR_CONFIG, "could not find key '%s' to delete", name);
		goto out;
	}

	if ((result = p_regcomp(&preg, regexp, REG_EXTENDED)) != 0) {
		git_error_set_regex(&preg, result);
		result = -1;
		goto out;
	}

	if ((result = config_write(b, name, key, &preg, NULL)) < 0)
		goto out;

	if ((result = config_refresh(cfg)) < 0)
		goto out;

out:
	git_config_entries_free(entries);
	git__free(key);
	regfree(&preg);
	return result;
}