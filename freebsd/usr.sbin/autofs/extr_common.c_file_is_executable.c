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
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  log_err (int,char*,char const*) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static bool
file_is_executable(const char *path)
{
	struct stat sb;
	int error;

	error = stat(path, &sb);
	if (error != 0)
		log_err(1, "cannot stat %s", path);
	if ((sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) ||
	    (sb.st_mode & S_IXOTH))
		return (true);
	return (false);
}