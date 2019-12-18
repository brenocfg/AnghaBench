#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_refspec ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refspec__dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refspec__parse (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_refspec_transform (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void assert_valid_transform(const char *refspec, const char *name, const char *result)
{
	git_refspec spec;
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_refspec__parse(&spec, refspec, true));
	cl_git_pass(git_refspec_transform(&buf, &spec, name));
	cl_assert_equal_s(result, buf.ptr);

	git_buf_dispose(&buf);
	git_refspec__dispose(&spec);
}