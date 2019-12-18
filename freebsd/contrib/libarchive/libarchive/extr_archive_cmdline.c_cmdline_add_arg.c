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
struct archive_cmdline {char** argv; int argc; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 char** realloc (char**,int) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
cmdline_add_arg(struct archive_cmdline *data, const char *arg)
{
	char **newargv;

	if (data->path == NULL)
		return (ARCHIVE_FAILED);

	newargv = realloc(data->argv, (data->argc + 2) * sizeof(char *));
	if (newargv == NULL)
		return (ARCHIVE_FATAL);
	data->argv = newargv;
	data->argv[data->argc] = strdup(arg);
	if (data->argv[data->argc] == NULL)
		return (ARCHIVE_FATAL);
	/* Set the terminator of argv. */
	data->argv[++data->argc] = NULL;
	return (ARCHIVE_OK);
}