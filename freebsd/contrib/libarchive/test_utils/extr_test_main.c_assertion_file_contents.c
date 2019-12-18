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
 int /*<<< orphan*/  hexdump (void const*,void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logprintf (char*,...) ; 
 char* malloc (int) ; 
 scalar_t__ memcmp (void const*,char*,int) ; 

int
assertion_file_contents(const char *filename, int line, const void *buff, int s, const char *fn)
{
	char *contents;
	FILE *f;
	int n;

	assertion_count(filename, line);

	f = fopen(fn, "rb");
	if (f == NULL) {
		failure_start(filename, line,
		    "File should exist: %s", fn);
		failure_finish(NULL);
		return (0);
	}
	contents = malloc(s * 2);
	n = (int)fread(contents, 1, s * 2, f);
	fclose(f);
	if (n == s && memcmp(buff, contents, s) == 0) {
		free(contents);
		return (1);
	}
	failure_start(filename, line, "File contents don't match");
	logprintf("  file=\"%s\"\n", fn);
	if (n > 0)
		hexdump(contents, buff, n > 512 ? 512 : n, 0);
	else {
		logprintf("  File empty, contents should be:\n");
		hexdump(buff, NULL, s > 512 ? 512 : s, 0);
	}
	failure_finish(NULL);
	free(contents);
	return (0);
}