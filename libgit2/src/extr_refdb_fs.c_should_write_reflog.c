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

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_LOGALLREFUPDATES ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
#define  GIT_LOGALLREFUPDATES_ALWAYS 130 
#define  GIT_LOGALLREFUPDATES_FALSE 129 
#define  GIT_LOGALLREFUPDATES_TRUE 128 
 int GIT_LOGALLREFUPDATES_UNSET ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  GIT_REFS_NOTES_DIR ; 
 int /*<<< orphan*/  GIT_REFS_REMOTES_DIR ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strcmp (char const*,int /*<<< orphan*/ ) ; 
 int git_repository__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_reflog (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int should_write_reflog(int *write, git_repository *repo, const char *name)
{
	int error, logall;

	error = git_repository__configmap_lookup(&logall, repo, GIT_CONFIGMAP_LOGALLREFUPDATES);
	if (error < 0)
		return error;

	/* Defaults to the opposite of the repo being bare */
	if (logall == GIT_LOGALLREFUPDATES_UNSET)
		logall = !git_repository_is_bare(repo);

	*write = 0;
	switch (logall) {
	case GIT_LOGALLREFUPDATES_FALSE:
		*write = 0;
		break;

	case GIT_LOGALLREFUPDATES_TRUE:
		/* Only write if it already has a log,
		 * or if it's under heads/, remotes/ or notes/
		 */
		*write = has_reflog(repo, name) ||
			!git__prefixcmp(name, GIT_REFS_HEADS_DIR) ||
			!git__strcmp(name, GIT_HEAD_FILE) ||
			!git__prefixcmp(name, GIT_REFS_REMOTES_DIR) ||
			!git__prefixcmp(name, GIT_REFS_NOTES_DIR);
		break;

	case GIT_LOGALLREFUPDATES_ALWAYS:
		*write = 1;
		break;
	}

	return 0;
}