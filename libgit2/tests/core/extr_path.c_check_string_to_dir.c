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
 int /*<<< orphan*/  cl_assert (char*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__malloc (size_t) ; 
 int /*<<< orphan*/  git_path_string_to_dir (char*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void
check_string_to_dir(
	const char* path,
	size_t      maxlen,
    const char* expected)
{
	size_t len = strlen(path);
	char *buf = git__malloc(len + 2);
	cl_assert(buf);

	strncpy(buf, path, len + 2);

	git_path_string_to_dir(buf, maxlen);

	cl_assert_equal_s(expected, buf);

	git__free(buf);
}