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
typedef  int /*<<< orphan*/  git_win32_utf8_path ;
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_win32_path_readlink_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_win32_path_to_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t min (size_t,size_t) ; 

int p_readlink(const char *path, char *buf, size_t bufsiz)
{
	git_win32_path path_w, target_w;
	git_win32_utf8_path target;
	int len;

	/* readlink(2) does not NULL-terminate the string written
	 * to the target buffer. Furthermore, the target buffer need
	 * not be large enough to hold the entire result. A truncated
	 * result should be written in this case. Since this truncation
	 * could occur in the middle of the encoding of a code point,
	 * we need to buffer the result on the stack. */

	if (git_win32_path_from_utf8(path_w, path) < 0 ||
		git_win32_path_readlink_w(target_w, path_w) < 0 ||
		(len = git_win32_path_to_utf8(target, target_w)) < 0)
		return -1;

	bufsiz = min((size_t)len, bufsiz);
	memcpy(buf, target, bufsiz);

	return (int)bufsiz;
}