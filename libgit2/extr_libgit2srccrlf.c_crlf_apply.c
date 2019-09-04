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
typedef  int /*<<< orphan*/  git_filter_source ;
typedef  int /*<<< orphan*/  git_filter ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ GIT_FILTER_SMUDGE ; 
 int crlf_apply_to_odb (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int crlf_apply_to_workdir (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int crlf_check (int /*<<< orphan*/ *,void**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_filter_source_mode (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int crlf_apply(
	git_filter *self,
	void **payload, /* may be read and/or set */
	git_buf *to,
	const git_buf *from,
	const git_filter_source *src)
{
	/* initialize payload in case `check` was bypassed */
	if (!*payload) {
		int error = crlf_check(self, payload, src, NULL);

		if (error < 0)
			return error;
	}

	if (git_filter_source_mode(src) == GIT_FILTER_SMUDGE)
		return crlf_apply_to_workdir(*payload, to, from);
	else
		return crlf_apply_to_odb(*payload, to, from, src);
}