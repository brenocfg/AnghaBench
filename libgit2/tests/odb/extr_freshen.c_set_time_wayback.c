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
struct stat {int dummy; } ;
struct p_timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  p_lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  p_utimes (int /*<<< orphan*/ ,struct p_timeval*) ; 

__attribute__((used)) static void set_time_wayback(struct stat *out, const char *fn)
{
	git_buf fullpath = GIT_BUF_INIT;
	struct p_timeval old[2];

	old[0].tv_sec = 1234567890;
	old[0].tv_usec = 0;
	old[1].tv_sec = 1234567890;
	old[1].tv_usec = 0;

	git_buf_joinpath(&fullpath, "testrepo.git/objects", fn);

	cl_must_pass(p_utimes(git_buf_cstr(&fullpath), old));
	cl_must_pass(p_lstat(git_buf_cstr(&fullpath), out));
	git_buf_dispose(&fullpath);
}