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
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  check_mailmap_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mailmap_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  g_mailmap ; 
 int /*<<< orphan*/  git_buf_attach_notowned (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_text_lf_to_crlf (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_mailmap_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolved ; 
 int /*<<< orphan*/  resolved_untracked ; 
 int /*<<< orphan*/  string_mailmap ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_mailmap_parsing__windows_string(void)
{
	git_buf unixbuf = GIT_BUF_INIT;
	git_buf winbuf = GIT_BUF_INIT;

	/* Parse with windows-style line endings */
	git_buf_attach_notowned(&unixbuf, string_mailmap, strlen(string_mailmap));
	cl_git_pass(git_buf_text_lf_to_crlf(&winbuf, &unixbuf));

	cl_git_pass(git_mailmap_from_buffer(&g_mailmap, winbuf.ptr, winbuf.size));
	git_buf_dispose(&winbuf);

	/* We should have parsed all of the entries */
	check_mailmap_entries(g_mailmap, entries, ARRAY_SIZE(entries));

	/* Check that resolving the entries works */
	check_mailmap_resolve(g_mailmap, resolved, ARRAY_SIZE(resolved));
	check_mailmap_resolve(
		g_mailmap, resolved_untracked, ARRAY_SIZE(resolved_untracked));
}