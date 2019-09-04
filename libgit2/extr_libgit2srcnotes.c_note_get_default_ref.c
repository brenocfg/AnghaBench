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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_NOTES_DEFAULT_REF ; 
 char* git_config__get_string_force (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int note_get_default_ref(char **out, git_repository *repo)
{
	git_config *cfg;
	int ret = git_repository_config__weakptr(&cfg, repo);

	*out = (ret != 0) ? NULL : git_config__get_string_force(
		cfg, "core.notesref", GIT_NOTES_DEFAULT_REF);

	return ret;
}