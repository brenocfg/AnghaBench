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

/* Variables and functions */

void test_core_link__stat_dangling_junction(void)
{
#ifdef GIT_WIN32
	git_buf target_path = GIT_BUF_INIT;
	struct stat st;

	git_buf_join(&target_path, '/', clar_sandbox_path(), "stat_nonexistent_junctarget");

	p_mkdir("stat_nonexistent_junctarget", 0777);
	do_junction(git_buf_cstr(&target_path), "stat_dangling_junction");

	RemoveDirectory("stat_nonexistent_junctarget");

	cl_must_fail(p_stat("stat_nonexistent_junctarget", &st));
	cl_must_fail(p_stat("stat_dangling_junction", &st));

	git_buf_dispose(&target_path);
#endif
}