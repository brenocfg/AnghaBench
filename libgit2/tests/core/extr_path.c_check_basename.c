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
struct TYPE_5__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 char* git_path_basename (char const*) ; 
 scalar_t__ git_path_basename_r (TYPE_1__*,char const*) ; 

__attribute__((used)) static void
check_basename(const char *A, const char *B)
{
	git_buf base = GIT_BUF_INIT;
	char *base2;

	cl_assert(git_path_basename_r(&base, A) >= 0);
	cl_assert_equal_s(B, base.ptr);
	git_buf_dispose(&base);

	cl_assert((base2 = git_path_basename(A)) != NULL);
	cl_assert_equal_s(B, base2);
	git__free(base2);
}