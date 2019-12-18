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
 int /*<<< orphan*/  assert (int) ; 
 int error_invalid_local_file_uri (char const*) ; 
 int git__percent_decode (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int local_file_url_prefixlen (char const*) ; 

int git_path_fromurl(git_buf *local_path_out, const char *file_url)
{
	int offset;

	assert(local_path_out && file_url);

	if ((offset = local_file_url_prefixlen(file_url)) < 0 ||
		file_url[offset] == '\0' || file_url[offset] == '/')
		return error_invalid_local_file_uri(file_url);

#ifndef GIT_WIN32
	offset--;	/* A *nix absolute path starts with a forward slash */
#endif

	git_buf_clear(local_path_out);
	return git__percent_decode(local_path_out, file_url + offset);
}