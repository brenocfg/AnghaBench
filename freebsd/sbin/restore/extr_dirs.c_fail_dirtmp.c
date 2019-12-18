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
 scalar_t__ ENOSPC ; 
 char* _PATH_TMP ; 
 int /*<<< orphan*/  done (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
fail_dirtmp(char *filename)
{
	const char *tmpdir;

	warn("%s: cannot write directory database", filename);
	if (errno == ENOSPC) {
		if ((tmpdir = getenv("TMPDIR")) == NULL || tmpdir[0] == '\0')
			tmpdir = _PATH_TMP;
		fprintf(stderr, "Try making space in %s, %s\n%s\n", tmpdir,
		    "or set environment variable TMPDIR",
		    "to an alternate location with more disk space.");
	}
	done(1);
}