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
 char* basename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
usage(const char *progname)
{
	char *path;

	path = strdup(progname);

	fprintf(stderr, "usage: %s [-f format] [-o filename] filename [...]\n",
	    basename(path));
	fprintf(stderr, "\tsupported output formats: shell, text\n");
	exit(1);
}