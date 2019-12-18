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
typedef  int /*<<< orphan*/  git_describe_options ;
struct TYPE_4__ {char* dirty_suffix; } ;
typedef  TYPE_1__ git_describe_format_options ;

/* Variables and functions */
 TYPE_1__ GIT_DESCRIBE_FORMAT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DESCRIBE_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert_describe_workdir (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  repo ; 

void test_describe_t6120__workdir(void)
{
	git_describe_options opts = GIT_DESCRIBE_OPTIONS_INIT;
	git_describe_format_options fmt_opts = GIT_DESCRIBE_FORMAT_OPTIONS_INIT;

	assert_describe_workdir("A-*[0-9a-f]", repo, &opts, &fmt_opts);
	cl_git_mkfile("describe/file", "something different");

	fmt_opts.dirty_suffix = "-dirty";
	assert_describe_workdir("A-*[0-9a-f]-dirty", repo, &opts, &fmt_opts);
	fmt_opts.dirty_suffix = ".mod";
	assert_describe_workdir("A-*[0-9a-f].mod", repo, &opts, &fmt_opts);
}