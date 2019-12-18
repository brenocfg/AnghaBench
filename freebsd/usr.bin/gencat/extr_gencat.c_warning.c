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
 char* curline ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
warning(const char *cptr, const char *msg)
{
	fprintf(stderr, "%s: %s on line %ld\n", getprogname(), msg, lineno);
	fprintf(stderr, "%s\n", curline);
	if (cptr) {
		char   *tptr;
		for (tptr = curline; tptr < cptr; ++tptr)
			putc(' ', stderr);
		fprintf(stderr, "^\n");
	}
}