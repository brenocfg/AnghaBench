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
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_buf_quote (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diff_delta_format_path(
	git_buf *out, const char *prefix, const char *filename)
{
	if (git_buf_joinpath(out, prefix, filename) < 0)
		return -1;

	return git_buf_quote(out);
}