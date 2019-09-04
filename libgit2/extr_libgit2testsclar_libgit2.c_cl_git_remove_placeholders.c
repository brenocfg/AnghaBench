#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* filename; int /*<<< orphan*/  filename_len; } ;
typedef  TYPE_1__ remove_data ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int git_path_isdir (char const*) ; 
 int remove_placeholders_recurs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int cl_git_remove_placeholders(const char *directory_path, const char *filename)
{
	int error;
	remove_data data;
	git_buf buffer = GIT_BUF_INIT;

	if (git_path_isdir(directory_path) == false)
		return -1;

	if (git_buf_sets(&buffer, directory_path) < 0)
		return -1;

	data.filename = filename;
	data.filename_len = strlen(filename);

	error = remove_placeholders_recurs(&data, &buffer);

	git_buf_dispose(&buffer);

	return error;
}