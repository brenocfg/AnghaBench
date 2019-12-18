#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int min_line; int flags; int /*<<< orphan*/  newest_commit; } ;
typedef  TYPE_1__ git_blame_options ;

/* Variables and functions */
 TYPE_1__ GIT_BLAME_OPTIONS_INIT ; 
 int GIT_BLAME_TRACK_COPIES_ANY_COMMIT_COPIES ; 
 int GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES ; 
 int GIT_BLAME_TRACK_COPIES_SAME_COMMIT_MOVES ; 
 int GIT_BLAME_TRACK_COPIES_SAME_FILE ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

__attribute__((used)) static int normalize_options(
		git_blame_options *out,
		const git_blame_options *in,
		git_repository *repo)
{
	git_blame_options dummy = GIT_BLAME_OPTIONS_INIT;
	if (!in) in = &dummy;

	memcpy(out, in, sizeof(git_blame_options));

	/* No newest_commit => HEAD */
	if (git_oid_is_zero(&out->newest_commit)) {
		if (git_reference_name_to_id(&out->newest_commit, repo, "HEAD") < 0) {
			return -1;
		}
	}

	/* min_line 0 really means 1 */
	if (!out->min_line) out->min_line = 1;
	/* max_line 0 really means N, but we don't know N yet */

	/* Fix up option implications */
	if (out->flags & GIT_BLAME_TRACK_COPIES_ANY_COMMIT_COPIES)
		out->flags |= GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES;
	if (out->flags & GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES)
		out->flags |= GIT_BLAME_TRACK_COPIES_SAME_COMMIT_MOVES;
	if (out->flags & GIT_BLAME_TRACK_COPIES_SAME_COMMIT_MOVES)
		out->flags |= GIT_BLAME_TRACK_COPIES_SAME_FILE;

	return 0;
}