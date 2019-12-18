#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opts ;
struct TYPE_17__ {int from_glob; } ;
typedef  TYPE_1__ git_revwalk__push_options ;
struct TYPE_18__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_revwalk ;
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_19__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_BUF (TYPE_3__*) ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_REFS_DIR ; 
 TYPE_1__ GIT_REVWALK__PUSH_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int git_reference_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int git_reference_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_revwalk__push_ref (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 size_t strcspn (char const*,char*) ; 

int git_revwalk__push_glob(git_revwalk *walk, const char *glob, const git_revwalk__push_options *given_opts)
{
	git_revwalk__push_options opts = GIT_REVWALK__PUSH_OPTIONS_INIT;
	int error = 0;
	git_buf buf = GIT_BUF_INIT;
	git_reference *ref;
	git_reference_iterator *iter;
	size_t wildcard;

	assert(walk && glob);

	if (given_opts)
		memcpy(&opts, given_opts, sizeof(opts));

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

	opts.from_glob = true;
	while ((error = git_reference_next(&ref, iter)) == 0) {
		error = git_revwalk__push_ref(walk, git_reference_name(ref), &opts);
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