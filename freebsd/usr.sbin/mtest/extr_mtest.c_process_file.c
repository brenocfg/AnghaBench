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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ isblank (char) ; 
 int /*<<< orphan*/  process_cmd (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
process_file(char *fname, int s, int s6)
{
	char line[80];
	FILE *fp;
	char *lineptr;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		warn("fopen");
		return;
	}

	/* Skip comments and empty lines. */
	while (fgets(line, sizeof(line), fp) != NULL) {
		lineptr = line;
		while (isblank(*lineptr))
			lineptr++;
		if (*lineptr != '#' && *lineptr != '\n')
			process_cmd(lineptr, s, s6, fp);
	}

	fclose(fp);
}