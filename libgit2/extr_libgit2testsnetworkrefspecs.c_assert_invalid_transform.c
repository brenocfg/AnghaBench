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
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refspec__dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refspec__parse (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_refspec_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void assert_invalid_transform(const char *refspec, const char *name)
{
	git_refspec spec;
	git_buf buf = GIT_BUF_INIT;

	git_refspec__parse(&spec, refspec, true);
	cl_git_fail(git_refspec_transform(&buf, &spec, name));

	git_buf_dispose(&buf);
	git_refspec__dispose(&spec);
}