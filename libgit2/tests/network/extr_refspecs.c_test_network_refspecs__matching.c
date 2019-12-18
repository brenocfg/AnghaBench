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
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ git_refspec ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refspec__dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refspec__parse (TYPE_1__*,char*,int) ; 

void test_network_refspecs__matching(void)
{
	git_refspec spec;

	cl_git_pass(git_refspec__parse(&spec, ":", false));
	cl_assert_equal_s(":", spec.string);
	cl_assert_equal_s("", spec.src);
	cl_assert_equal_s("", spec.dst);

	git_refspec__dispose(&spec);
}