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
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static int file_url(git_buf *buf, const char *host, const char *path)
{
	if (path[0] == '/')
		path++;

	git_buf_clear(buf);
	return git_buf_printf(buf, "file://%s/%s", host, path);
}