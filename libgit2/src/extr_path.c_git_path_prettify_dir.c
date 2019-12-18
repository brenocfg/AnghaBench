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
 int git_path_prettify (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_path_to_dir (int /*<<< orphan*/ *) ; 

int git_path_prettify_dir(git_buf *path_out, const char *path, const char *base)
{
	int error = git_path_prettify(path_out, path, base);
	return (error < 0) ? error : git_path_to_dir(path_out);
}