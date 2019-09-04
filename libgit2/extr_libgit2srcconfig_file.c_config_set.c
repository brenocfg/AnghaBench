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
struct TYPE_5__ {scalar_t__ value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config_entries ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_6__ {int /*<<< orphan*/  header; } ;
typedef  TYPE_2__ diskfile_backend ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int config_refresh (int /*<<< orphan*/ *) ; 
 int config_write (TYPE_2__*,char const*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * diskfile_entries_take (int /*<<< orphan*/ *) ; 
 char* escape_value (char const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_config__normalize_name (char const*,char**) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ *) ; 
 int git_config_entries_get_unique (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int config_set(git_config_backend *cfg, const char *name, const char *value)
{
	diskfile_backend *b = (diskfile_backend *)cfg;
	git_config_entries *entries;
	git_config_entry *existing;
	char *key, *esc_value = NULL;
	int error;

	if ((error = git_config__normalize_name(name, &key)) < 0)
		return error;

	if ((entries = diskfile_entries_take(&b->header)) == NULL)
		return -1;

	/* Check whether we'd be modifying an included or multivar key */
	if ((error = git_config_entries_get_unique(&existing, entries, key)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto out;
		error = 0;
	} else if ((!existing->value && !value) ||
		   (existing->value && value && !strcmp(existing->value, value))) {
		/* don't update if old and new values already match */
		error = 0;
		goto out;
	}

	/* No early returns due to sanity checks, let's write it out and refresh */
	if (value) {
		esc_value = escape_value(value);
		GIT_ERROR_CHECK_ALLOC(esc_value);
	}

	if ((error = config_write(b, name, key, NULL, esc_value)) < 0)
		goto out;

	error = config_refresh(cfg);

out:
	git_config_entries_free(entries);
	git__free(esc_value);
	git__free(key);
	return error;
}