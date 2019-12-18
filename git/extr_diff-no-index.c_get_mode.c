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
struct stat {int st_mode; } ;

/* Variables and functions */
 int create_ce_mode (int) ; 
 int error (char*,char const*) ; 
 char const* file_from_standard_input ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int get_mode(const char *path, int *mode)
{
	struct stat st;

	if (!path || !strcmp(path, "/dev/null"))
		*mode = 0;
#ifdef GIT_WINDOWS_NATIVE
	else if (!strcasecmp(path, "nul"))
		*mode = 0;
#endif
	else if (path == file_from_standard_input)
		*mode = create_ce_mode(0666);
	else if (lstat(path, &st))
		return error("Could not access '%s'", path);
	else
		*mode = st.st_mode;
	return 0;
}