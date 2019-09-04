#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int git_config_delete_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_iterator_free (int /*<<< orphan*/ *) ; 
 int git_config_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int git_config_next (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* name_offset (size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_branch_config_related_entries(
	git_repository *repo,
	const char *remote_name)
{
	int error;
	git_config *config;
	git_config_entry *entry;
	git_config_iterator *iter;
	git_buf buf = GIT_BUF_INIT;

	if ((error = git_repository_config__weakptr(&config, repo)) < 0)
		return error;

	if ((error = git_config_iterator_glob_new(&iter, config, "branch\\..+\\.remote")) < 0)
		return error;

	/* find any branches with us as upstream and remove that config */
	while ((error = git_config_next(&entry, iter)) == 0) {
		const char *branch;
		size_t branch_len;

		if (strcmp(remote_name, entry->value))
			continue;

		branch = name_offset(&branch_len, entry->name);

		git_buf_clear(&buf);
		if (git_buf_printf(&buf, "branch.%.*s.merge", (int)branch_len, branch) < 0)
			break;

		if ((error = git_config_delete_entry(config, git_buf_cstr(&buf))) < 0) {
			if (error != GIT_ENOTFOUND)
				break;
			git_error_clear();
		}

		git_buf_clear(&buf);
		if (git_buf_printf(&buf, "branch.%.*s.remote", (int)branch_len, branch) < 0)
			break;

		if ((error = git_config_delete_entry(config, git_buf_cstr(&buf))) < 0) {
			if (error != GIT_ENOTFOUND)
				break;
			git_error_clear();
		}
	}

	if (error == GIT_ITEROVER)
		error = 0;

	git_buf_dispose(&buf);
	git_config_iterator_free(iter);
	return error;
}