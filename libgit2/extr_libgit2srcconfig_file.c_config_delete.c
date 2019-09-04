#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config_entries ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_6__ {int /*<<< orphan*/  header; } ;
typedef  TYPE_2__ diskfile_backend ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int config_refresh (int /*<<< orphan*/ *) ; 
 int config_write (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * diskfile_entries_take (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_config__normalize_name (char const*,char**) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ *) ; 
 int git_config_entries_get_unique (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int config_delete(git_config_backend *cfg, const char *name)
{
	diskfile_backend *b = (diskfile_backend *)cfg;
	git_config_entries *entries = NULL;
	git_config_entry *entry;
	char *key = NULL;
	int error;

	if ((error = git_config__normalize_name(name, &key)) < 0)
		goto out;

	if ((entries = diskfile_entries_take(&b->header)) == NULL)
		goto out;

	/* Check whether we'd be modifying an included or multivar key */
	if ((error = git_config_entries_get_unique(&entry, entries, key)) < 0) {
		if (error == GIT_ENOTFOUND)
			git_error_set(GIT_ERROR_CONFIG, "could not find key '%s' to delete", name);
		goto out;
	}

	if ((error = config_write(b, name, entry->name, NULL, NULL)) < 0)
		goto out;

	if ((error =  config_refresh(cfg)) < 0)
		goto out;

out:
	git_config_entries_free(entries);
	git__free(key);
	return error;
}