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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REPOSITORY_OPEN_CROSS_FS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int find_repo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 

int git_repository_discover(
	git_buf *out,
	const char *start_path,
	int across_fs,
	const char *ceiling_dirs)
{
	uint32_t flags = across_fs ? GIT_REPOSITORY_OPEN_CROSS_FS : 0;

	assert(start_path);

	git_buf_sanitize(out);

	return find_repo(out, NULL, NULL, NULL, start_path, flags, ceiling_dirs);
}