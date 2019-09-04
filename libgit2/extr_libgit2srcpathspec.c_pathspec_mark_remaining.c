#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pathspec_match_context {int dummy; } ;
struct TYPE_4__ {size_t length; } ;
typedef  TYPE_1__ git_vector ;
typedef  int /*<<< orphan*/  git_bitvec ;
typedef  int /*<<< orphan*/  git_attr_fnmatch ;

/* Variables and functions */
 scalar_t__ git_bitvec_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * git_vector_get (TYPE_1__*,size_t) ; 
 scalar_t__ pathspec_mark_pattern (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ pathspec_match_one (int /*<<< orphan*/  const*,struct pathspec_match_context*,char const*) ; 

__attribute__((used)) static size_t pathspec_mark_remaining(
	git_bitvec *used,
	git_vector *patterns,
	struct pathspec_match_context *ctxt,
	size_t start,
	const char *path0,
	const char *path1)
{
	size_t count = 0;

	if (path1 == path0)
		path1 = NULL;

	for (; start < patterns->length; ++start) {
		const git_attr_fnmatch *pat = git_vector_get(patterns, start);

		if (git_bitvec_get(used, start))
			continue;

		if (path0 && pathspec_match_one(pat, ctxt, path0) > 0)
			count += pathspec_mark_pattern(used, start);
		else if (path1 && pathspec_match_one(pat, ctxt, path1) > 0)
			count += pathspec_mark_pattern(used, start);
	}

	return count;
}