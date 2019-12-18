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
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_text_unescape (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void assert_unescape(char *expected, char *to_unescape) {
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_sets(&buf, to_unescape));
	git_buf_text_unescape(&buf);
	cl_assert_equal_s(expected, buf.ptr);
	cl_assert_equal_sz(strlen(expected), buf.size);

	git_buf_dispose(&buf);
}