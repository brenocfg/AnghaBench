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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_attr_session ;
typedef  int /*<<< orphan*/  git_attr_file_source ;
typedef  int /*<<< orphan*/  git_attr_file_parser ;
typedef  int /*<<< orphan*/  git_attr_file_entry ;
typedef  int /*<<< orphan*/  git_attr_file ;
typedef  int /*<<< orphan*/  git_attr_cache ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int attr_cache_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  attr_cache_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int attr_cache_upsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_attr_file__free (int /*<<< orphan*/ *) ; 
 int git_attr_file__load (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int git_attr_file__out_of_date (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/ * git_repository_attr_cache (int /*<<< orphan*/ *) ; 

int git_attr_cache__get(
	git_attr_file **out,
	git_repository *repo,
	git_attr_session *attr_session,
	git_attr_file_source source,
	const char *base,
	const char *filename,
	git_attr_file_parser parser,
	bool allow_macros)
{
	int error = 0;
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_attr_file_entry *entry = NULL;
	git_attr_file *file = NULL, *updated = NULL;

	if ((error = attr_cache_lookup(
			&file, &entry, repo, attr_session, source, base, filename)) < 0)
		return error;

	/* load file if we don't have one or if existing one is out of date */
	if (!file || (error = git_attr_file__out_of_date(repo, attr_session, file)) > 0)
		error = git_attr_file__load(&updated, repo, attr_session, entry, source, parser, allow_macros);

	/* if we loaded the file, insert into and/or update cache */
	if (updated) {
		if ((error = attr_cache_upsert(cache, updated)) < 0)
			git_attr_file__free(updated);
		else {
			git_attr_file__free(file); /* offset incref from lookup */
			file = updated;
		}
	}

	/* if file could not be loaded */
	if (error < 0) {
		/* remove existing entry */
		if (file) {
			attr_cache_remove(cache, file);
			git_attr_file__free(file); /* offset incref from lookup */
			file = NULL;
		}
		/* no error if file simply doesn't exist */
		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			error = 0;
		}
	}

	*out = file;
	return error;
}