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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 char* compress_program ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int file_is_tmp (char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  getstr (int) ; 
 int /*<<< orphan*/ * popen (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sort_free (char*) ; 
 char* sort_malloc (size_t) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int umask (int) ; 

FILE *
openfile(const char *fn, const char *mode)
{
	FILE *file;

	if (strcmp(fn, "-") == 0) {
		return ((mode && mode[0] == 'r') ? stdin : stdout);
	} else {
		mode_t orig_file_mask = 0;
		int is_tmp = file_is_tmp(fn);

		if (is_tmp && (mode[0] == 'w'))
			orig_file_mask = umask(S_IWGRP | S_IWOTH |
			    S_IRGRP | S_IROTH);

		if (is_tmp && (compress_program != NULL)) {
			char *cmd;
			size_t cmdsz;

			cmdsz = strlen(fn) + 128;
			cmd = sort_malloc(cmdsz);

			fflush(stdout);

			if (mode[0] == 'r')
				snprintf(cmd, cmdsz - 1, "cat %s | %s -d",
				    fn, compress_program);
			else if (mode[0] == 'w')
				snprintf(cmd, cmdsz - 1, "%s > %s",
				    compress_program, fn);
			else
				err(2, "%s", getstr(7));

			if ((file = popen(cmd, mode)) == NULL)
				err(2, NULL);

			sort_free(cmd);

		} else
			if ((file = fopen(fn, mode)) == NULL)
				err(2, NULL);

		if (is_tmp && (mode[0] == 'w'))
			umask(orig_file_mask);
	}

	return (file);
}