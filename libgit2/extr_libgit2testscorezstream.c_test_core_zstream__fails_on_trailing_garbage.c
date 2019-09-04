#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_zstream_deflatebuf (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  git_zstream_inflatebuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_core_zstream__fails_on_trailing_garbage(void)
{
	git_buf deflated = GIT_BUF_INIT, inflated = GIT_BUF_INIT;
	char i = 0;

	/* compress a simple string */
	git_zstream_deflatebuf(&deflated, "foobar!!", 8);

	/* append some garbage */
	for (i = 0; i < 10; i++) {
		git_buf_putc(&deflated, i);
	}

	cl_git_fail(git_zstream_inflatebuf(&inflated, deflated.ptr, deflated.size));

	git_buf_dispose(&deflated);
	git_buf_dispose(&inflated);
}