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
 int FALSE ; 
 int /*<<< orphan*/  File_list ; 
 int /*<<< orphan*/  File_tail ; 
 scalar_t__ Find_files ; 
 char* Fortune_path ; 
 char** Fortune_path_arr ; 
 int Fortunes_only ; 
 int NO_PROB ; 
 int TRUE ; 
 scalar_t__ add_file (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
form_file_list(char **files, int file_cnt)
{
	int	i, percent;
	char	*sp;
	char	**pstr;

	if (file_cnt == 0) {
		if (Find_files) {
			Fortunes_only = TRUE;
			pstr = Fortune_path_arr;
			i = 0;
			while (*pstr) {
				i += add_file(NO_PROB, *pstr++, NULL,
					      &File_list, &File_tail, NULL);
			}
			Fortunes_only = FALSE;
			if (!i) {
				fprintf(stderr, "No fortunes found in %s.\n",
				    Fortune_path);
			}
			return (i != 0);
		} else {
			pstr = Fortune_path_arr;
			i = 0;
			while (*pstr) {
				i += add_file(NO_PROB, "fortunes", *pstr++,
					      &File_list, &File_tail, NULL);
			}
			if (!i) {
				fprintf(stderr, "No fortunes found in %s.\n",
				    Fortune_path);
			}
			return (i != 0);
		}
	}
	for (i = 0; i < file_cnt; i++) {
		percent = NO_PROB;
		if (!isdigit((unsigned char)files[i][0]))
			sp = files[i];
		else {
			percent = 0;
			for (sp = files[i]; isdigit((unsigned char)*sp); sp++)
				percent = percent * 10 + *sp - '0';
			if (percent > 100) {
				fprintf(stderr, "percentages must be <= 100\n");
				return (FALSE);
			}
			if (*sp == '.') {
				fprintf(stderr, "percentages must be integers\n");
				return (FALSE);
			}
			/*
			 * If the number isn't followed by a '%', then
			 * it was not a percentage, just the first part
			 * of a file name which starts with digits.
			 */
			if (*sp != '%') {
				percent = NO_PROB;
				sp = files[i];
			}
			else if (*++sp == '\0') {
				if (++i >= file_cnt) {
					fprintf(stderr, "percentages must precede files\n");
					return (FALSE);
				}
				sp = files[i];
			}
		}
		if (strcmp(sp, "all") == 0) {
			pstr = Fortune_path_arr;
			i = 0;
			while (*pstr) {
				i += add_file(NO_PROB, *pstr++, NULL,
					      &File_list, &File_tail, NULL);
			}
			if (!i) {
				fprintf(stderr, "No fortunes found in %s.\n",
				    Fortune_path);
				return (FALSE);
			}
		} else if (!add_file(percent, sp, NULL, &File_list,
				     &File_tail, NULL)) {
 			return (FALSE);
		}
	}

	return (TRUE);
}