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
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int default_fetchspec_for_name(git_buf *buf, const char *name)
{
	if (git_buf_printf(buf, "+refs/heads/*:refs/remotes/%s/*", name) < 0)
		return -1;

	return 0;
}