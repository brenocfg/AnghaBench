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
struct file_name {char* path; scalar_t__ exists; } ;

/* Variables and functions */
 int MAX_FILE ; 
 size_t NEW_FILE ; 
 scalar_t__ ok_to_create_file ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
posix_name(const struct file_name *names, bool assume_exists)
{
	char *path = NULL;
	int i;

	/*
	 * POSIX states that the filename will be chosen from one
	 * of the old, new and index names (in that order) if
	 * the file exists relative to CWD after -p stripping.
	 */
	for (i = 0; i < MAX_FILE; i++) {
		if (names[i].path != NULL && names[i].exists) {
			path = names[i].path;
			break;
		}
	}
	if (path == NULL && !assume_exists) {
		/*
		 * No files found, check to see if the diff could be
		 * creating a new file.
		 */
		if (path == NULL && ok_to_create_file &&
		    names[NEW_FILE].path != NULL)
			path = names[NEW_FILE].path;
	}

	return path ? xstrdup(path) : NULL;
}