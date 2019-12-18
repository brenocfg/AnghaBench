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
 int git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int git_path_fromurl (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_path_is_local_file_url (char const*) ; 

int git_path_from_url_or_path(git_buf *local_path_out, const char *url_or_path)
{
	if (git_path_is_local_file_url(url_or_path))
		return git_path_fromurl(local_path_out, url_or_path);
	else
		return git_buf_sets(local_path_out, url_or_path);
}