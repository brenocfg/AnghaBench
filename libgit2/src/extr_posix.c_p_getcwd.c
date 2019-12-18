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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* getcwd (char*,size_t) ; 
 int /*<<< orphan*/  git_path_mkposix (char*) ; 
 int /*<<< orphan*/  git_path_string_to_dir (char*,size_t) ; 

int p_getcwd(char *buffer_out, size_t size)
{
	char *cwd_buffer;

	assert(buffer_out && size > 0);

	cwd_buffer = getcwd(buffer_out, size);

	if (cwd_buffer == NULL)
		return -1;

	git_path_mkposix(buffer_out);
	git_path_string_to_dir(buffer_out, size); /* append trailing slash */

	return 0;
}