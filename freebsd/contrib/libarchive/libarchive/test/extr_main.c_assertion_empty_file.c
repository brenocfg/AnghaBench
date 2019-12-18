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
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logprintf (char*,...) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int
assertion_empty_file(const char *filename, int line, const char *f1)
{
	char buff[1024];
	struct stat st;
	ssize_t s;
	FILE *f;

	assertion_count(filename, line);

	if (stat(f1, &st) != 0) {
		failure_start(filename, line, "Stat failed: %s", f1);
		failure_finish(NULL);
		return (0);
	}
	if (st.st_size == 0)
		return (1);

	failure_start(filename, line, "File should be empty: %s", f1);
	logprintf("    File size: %d\n", (int)st.st_size);
	logprintf("    Contents:\n");
	f = fopen(f1, "rb");
	if (f == NULL) {
		logprintf("    Unable to open %s\n", f1);
	} else {
		s = ((off_t)sizeof(buff) < st.st_size) ?
		    (ssize_t)sizeof(buff) : (ssize_t)st.st_size;
		s = fread(buff, 1, s, f);
		hexdump(buff, NULL, s, 0);
		fclose(f);
	}
	failure_finish(NULL);
	return (0);
}