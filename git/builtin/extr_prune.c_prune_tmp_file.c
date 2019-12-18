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
struct stat {scalar_t__ st_mtime; } ;

/* Variables and functions */
 int error (char*,char const*) ; 
 scalar_t__ expire ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ show_only ; 
 int /*<<< orphan*/  unlink_or_warn (char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int prune_tmp_file(const char *fullpath)
{
	struct stat st;
	if (lstat(fullpath, &st))
		return error("Could not stat '%s'", fullpath);
	if (st.st_mtime > expire)
		return 0;
	if (show_only || verbose)
		printf("Removing stale temporary file %s\n", fullpath);
	if (!show_only)
		unlink_or_warn(fullpath);
	return 0;
}