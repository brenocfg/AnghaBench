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
struct archive_cmdline {char* path; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 char* realloc (char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
cmdline_set_path(struct archive_cmdline *data, const char *path)
{
	char *newptr;

	newptr = realloc(data->path, strlen(path) + 1);
	if (newptr == NULL)
		return (ARCHIVE_FATAL);
	data->path = newptr;
	strcpy(data->path, path);
	return (ARCHIVE_OK);
}