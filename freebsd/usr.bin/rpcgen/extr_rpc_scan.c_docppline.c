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
 int atoi (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strlen (char*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
docppline(char *line, int *lineno, const char **fname)
{
	char *file;
	int num;
	char *p;

	line++;
	while (isspace(*line)) {
		line++;
	}
	num = atoi(line);
	while (isdigit(*line)) {
		line++;
	}
	while (isspace(*line)) {
		line++;
	}
	if (*line != '"') {
		error("preprocessor error");
	}
	line++;
	p = file = xmalloc(strlen(line) + 1);
	while (*line && *line != '"') {
		*p++ = *line++;
	}
	if (*line == 0) {
		error("preprocessor error");
	}
	*p = 0;
	if (*file == 0) {
		*fname = NULL;
		free(file);
	} else {
		*fname = file;
	}
	*lineno = num - 1;
}