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
 int /*<<< orphan*/  GIT_UNUSED (size_t) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_iconv (int /*<<< orphan*/ *,char const**,size_t*) ; 
 int /*<<< orphan*/  ic ; 
 size_t strlen (char const*) ; 

void test_core_iconv__unchanged(void)
{
#ifdef GIT_USE_ICONV
	const char *data = "Ascii data", *original = data;
	size_t datalen = strlen(data);

	cl_git_pass(git_path_iconv(&ic, &data, &datalen));
	GIT_UNUSED(datalen);

	/* There are no high bits set, so this should leave data untouched */
	cl_assert(data == original);
#endif
}