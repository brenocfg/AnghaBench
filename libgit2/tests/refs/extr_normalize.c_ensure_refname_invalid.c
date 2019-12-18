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
typedef  int /*<<< orphan*/  buffer_out ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int GIT_REFNAME_MAX ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_normalize_name (char*,int,char const*,unsigned int) ; 

__attribute__((used)) static void ensure_refname_invalid(unsigned int flags, const char *input_refname)
{
	char buffer_out[GIT_REFNAME_MAX];

	cl_assert_equal_i(
		GIT_EINVALIDSPEC,
		git_reference_normalize_name(buffer_out, sizeof(buffer_out), input_refname, flags));
}