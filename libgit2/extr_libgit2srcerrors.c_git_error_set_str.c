#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {int /*<<< orphan*/  error_buf; } ;

/* Variables and functions */
 TYPE_1__* GIT_GLOBAL ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  set_error_from_buffer (int) ; 

void git_error_set_str(int error_class, const char *string)
{
	git_buf *buf = &GIT_GLOBAL->error_buf;

	assert(string);

	if (!string)
		return;

	git_buf_clear(buf);
	git_buf_puts(buf, string);
	if (!git_buf_oom(buf))
		set_error_from_buffer(error_class);
}