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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 scalar_t__ openpam_straddch (char**,size_t*,size_t*,int) ; 

char *
openpam_readline(FILE *f, int *lineno, size_t *lenp)
{
	char *line;
	size_t len, size;
	int ch;

	line = NULL;
	if (openpam_straddch(&line, &size, &len, 0) != 0)
		return (NULL);
	for (;;) {
		ch = fgetc(f);
		/* strip comment */
		if (ch == '#') {
			do {
				ch = fgetc(f);
			} while (ch != EOF && ch != '\n');
		}
		/* eof */
		if (ch == EOF) {
			/* done */
			break;
		}
		/* eol */
		if (ch == '\n') {
			if (lineno != NULL)
				++*lineno;
			/* skip blank lines */
			if (len == 0)
				continue;
			/* continuation */
			if (line[len - 1] == '\\') {
				line[--len] = '\0';
				continue;
			}
			/* done */
			break;
		}
		/* anything else */
		if (openpam_straddch(&line, &size, &len, ch) != 0)
			goto fail;
	}
	if (len == 0)
		goto fail;
	if (lenp != NULL)
		*lenp = len;
	return (line);
fail:
	FREE(line);
	return (NULL);
}