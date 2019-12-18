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
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hexdump (char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logprintf (char*,...) ; 
 char* malloc (int) ; 
 scalar_t__ strlen (char const*) ; 

int
assertion_text_file_contents(const char *filename, int line, const char *buff, const char *fn)
{
	char *contents;
	const char *btxt, *ftxt;
	FILE *f;
	int n, s;

	assertion_count(filename, line);
	f = fopen(fn, "r");
	if (f == NULL) {
		failure_start(filename, line,
		    "File doesn't exist: %s", fn);
		failure_finish(NULL);
		return (0);
	}
	s = (int)strlen(buff);
	contents = malloc(s * 2 + 128);
	n = (int)fread(contents, 1, s * 2 + 128 - 1, f);
	if (n >= 0)
		contents[n] = '\0';
	fclose(f);
	/* Compare texts. */
	btxt = buff;
	ftxt = (const char *)contents;
	while (*btxt != '\0' && *ftxt != '\0') {
		if (*btxt == *ftxt) {
			++btxt;
			++ftxt;
			continue;
		}
		if (btxt[0] == '\n' && ftxt[0] == '\r' && ftxt[1] == '\n') {
			/* Pass over different new line characters. */
			++btxt;
			ftxt += 2;
			continue;
		}
		break;
	}
	if (*btxt == '\0' && *ftxt == '\0') {
		free(contents);
		return (1);
	}
	failure_start(filename, line, "Contents don't match");
	logprintf("  file=\"%s\"\n", fn);
	if (n > 0) {
		hexdump(contents, buff, n, 0);
		logprintf("  expected\n", fn);
		hexdump(buff, contents, s, 0);
	} else {
		logprintf("  File empty, contents should be:\n");
		hexdump(buff, NULL, s, 0);
	}
	failure_finish(NULL);
	free(contents);
	return (0);
}