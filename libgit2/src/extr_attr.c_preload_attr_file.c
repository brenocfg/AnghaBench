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
typedef  int /*<<< orphan*/  git_attr_file ;

/* Variables and functions */
 int git_attr_cache__get (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_attr_file__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_attr_file__parse_buffer ; 

__attribute__((used)) static int preload_attr_file(
	git_repository *repo,
	git_attr_session *attr_session,
	git_attr_file_source source,
	const char *base,
	const char *file,
	bool allow_macros)
{
	int error;
	git_attr_file *preload = NULL;

	if (!file)
		return 0;
	if (!(error = git_attr_cache__get(&preload, repo, attr_session, source, base, file,
					  git_attr_file__parse_buffer, allow_macros)))
		git_attr_file__free(preload);

	return error;
}