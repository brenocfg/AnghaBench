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
struct TYPE_4__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_1__ git_refspec ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_refspec_dst_matches (TYPE_1__ const*,char const*) ; 
 int refspec_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int git_refspec_rtransform(git_buf *out, const git_refspec *spec, const char *name)
{
	assert(out && spec && name);
	git_buf_sanitize(out);

	if (!git_refspec_dst_matches(spec, name)) {
		git_error_set(GIT_ERROR_INVALID, "ref '%s' doesn't match the destination", name);
		return -1;
	}

	if (!spec->pattern)
		return git_buf_puts(out, spec->src);

	return refspec_transform(out, spec->dst, spec->src, name);
}