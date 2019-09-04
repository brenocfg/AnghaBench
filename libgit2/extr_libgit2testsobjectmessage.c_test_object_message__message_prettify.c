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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_message_prettify (TYPE_1__*,char*,int,char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_object_message__message_prettify(void)
{
	git_buf buffer;

	memset(&buffer, 0, sizeof(buffer));
	cl_git_pass(git_message_prettify(&buffer, "", 0, '#'));
	cl_assert_equal_s(buffer.ptr, "");
	git_buf_dispose(&buffer);
	cl_git_pass(git_message_prettify(&buffer, "", 1, '#'));
	cl_assert_equal_s(buffer.ptr, "");
	git_buf_dispose(&buffer);

	cl_git_pass(git_message_prettify(&buffer, "Short", 0, '#'));
	cl_assert_equal_s("Short\n", buffer.ptr);
	git_buf_dispose(&buffer);
	cl_git_pass(git_message_prettify(&buffer, "Short", 1, '#'));
	cl_assert_equal_s("Short\n", buffer.ptr);
	git_buf_dispose(&buffer);

	cl_git_pass(git_message_prettify(&buffer, "This is longer\nAnd multiline\n# with some comments still in\n", 0, '#'));
	cl_assert_equal_s(buffer.ptr, "This is longer\nAnd multiline\n# with some comments still in\n");
	git_buf_dispose(&buffer);

	cl_git_pass(git_message_prettify(&buffer, "This is longer\nAnd multiline\n# with some comments still in\n", 1, '#'));
	cl_assert_equal_s(buffer.ptr, "This is longer\nAnd multiline\n");
	git_buf_dispose(&buffer);
}