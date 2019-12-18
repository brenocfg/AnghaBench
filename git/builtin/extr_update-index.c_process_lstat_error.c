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
 int error (char*,char const*,char*) ; 
 scalar_t__ is_missing_file_error (int) ; 
 int remove_one_path (char const*) ; 
 char* strerror (int) ; 

__attribute__((used)) static int process_lstat_error(const char *path, int err)
{
	if (is_missing_file_error(err))
		return remove_one_path(path);
	return error("lstat(\"%s\"): %s", path, strerror(err));
}