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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_merge_driver_source ;
typedef  int /*<<< orphan*/  const git_merge_driver ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int test_driver_apply(
	git_merge_driver *s,
	const char **path_out,
	uint32_t *mode_out,
	git_buf *merged_out,
	const char *filter_name,
	const git_merge_driver_source *src)
{
	GIT_UNUSED(s);
	GIT_UNUSED(src);

	*path_out = "applied.txt";
	*mode_out = GIT_FILEMODE_BLOB;

	return git_buf_printf(merged_out, "This is the `%s` driver.\n",
		filter_name);
}