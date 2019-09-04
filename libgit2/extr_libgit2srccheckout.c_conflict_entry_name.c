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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ git_buf_putc (int /*<<< orphan*/ *,char) ; 
 scalar_t__ git_buf_puts (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int conflict_entry_name(
	git_buf *out,
	const char *side_name,
	const char *filename)
{
	if (git_buf_puts(out, side_name) < 0 ||
		git_buf_putc(out, ':') < 0 ||
		git_buf_puts(out, filename) < 0)
		return -1;

	return 0;
}