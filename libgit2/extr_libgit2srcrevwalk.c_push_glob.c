#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_BUF (TYPE_2__*) ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_REFS_DIR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int git_reference_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int git_reference_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int push_ref (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static int push_glob(git_revwalk *walk, const char *glob, int hide)
{
	int error = 0;
	git_buf buf = GIT_BUF_INIT;
	git_reference *ref;
	git_reference_iterator *iter;
	size_t wildcard;

	assert(walk && glob);

	/* refs/ is implied if not given in the glob */
	if (git__prefixcmp(glob, GIT_REFS_DIR) != 0)
		git_buf_joinpath(&buf, GIT_REFS_DIR, glob);
	else
		git_buf_puts(&buf, glob);
	GIT_ERROR_CHECK_ALLOC_BUF(&buf);

	/* If no '?', '*' or '[' exist, we append '/ *' to the glob */
	wildcard = strcspn(glob, "?*[");
	if (!glob[wildcard])
		git_buf_put(&buf, "/*", 2);

	if ((error = git_reference_iterator_glob_new(&iter, walk->repo, buf.ptr)) < 0)
		goto out;

	while ((error = git_reference_next(&ref, iter)) == 0) {
		error = push_ref(walk, git_reference_name(ref), hide, true);
		git_reference_free(ref);
		if (error < 0)
			break;
	}
	git_reference_iterator_free(iter);

	if (error == GIT_ITEROVER)
		error = 0;
out:
	git_buf_dispose(&buf);
	return error;
}