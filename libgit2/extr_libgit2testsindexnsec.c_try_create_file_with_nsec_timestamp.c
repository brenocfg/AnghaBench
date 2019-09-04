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
struct stat {scalar_t__ st_mtime_nsec; scalar_t__ st_ctime_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_stat (char const*,struct stat*) ; 

__attribute__((used)) static bool try_create_file_with_nsec_timestamp(const char *path)
{
	struct stat st;
	int try;

	/* retry a few times to avoid nanos *actually* equal 0 race condition */
	for (try = 0; try < 3; try++) {
		cl_git_mkfile(path, "This is hopefully a file with nanoseconds!");

		cl_must_pass(p_stat(path, &st));

		if (st.st_ctime_nsec && st.st_mtime_nsec)
			return true;
	}

	return false;
}