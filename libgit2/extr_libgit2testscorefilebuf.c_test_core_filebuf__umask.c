#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
typedef  int mode_t ;
struct TYPE_6__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 TYPE_1__ GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_commit (TYPE_1__*) ; 
 int /*<<< orphan*/  git_filebuf_open (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int p_umask (int) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_filebuf__umask(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	char test[] = "test";
	struct stat statbuf;
	mode_t mask, os_mask;

#ifdef GIT_WIN32
	os_mask = 0600;
#else
	os_mask = 0777;
#endif

	p_umask(mask = p_umask(0));

	cl_assert(file.buffer == NULL);

	cl_git_pass(git_filebuf_open(&file, test, 0, 0666));
	cl_assert(file.buffer != NULL);
	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));
	cl_assert(file.buffer != NULL);

	cl_git_pass(git_filebuf_commit(&file));
	cl_assert(file.buffer == NULL);

	cl_must_pass(p_stat("test", &statbuf));
	cl_assert_equal_i(statbuf.st_mode & os_mask, (0666 & ~mask) & os_mask);

	cl_must_pass(p_unlink(test));
}