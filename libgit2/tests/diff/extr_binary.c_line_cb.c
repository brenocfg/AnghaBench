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
typedef  void git_diff_line ;
typedef  void git_diff_hunk ;
typedef  void git_diff_delta ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_fail (char*) ; 

__attribute__((used)) static int line_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *payload)
{
	GIT_UNUSED(delta);
	GIT_UNUSED(hunk);
	GIT_UNUSED(line);
	GIT_UNUSED(payload);

	cl_fail("did not expect line callback");
	return 0;
}