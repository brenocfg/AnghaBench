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
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
	    "indent_wrapper [-v] [-d] [-D] [-g <githash>]\n"
	    "\t" "[-s <svnrevision> ] [ -t <tool> ] [ -c <command> ]\n"
	    "\t" "-v        Increase verbosity\n"
	    "\t" "-d        Check output from git diff\n"
	    "\t" "-D        Check output from svn diff\n"
	    "\t" "-c <cmd>  Set custom command to produce diff\n"
	    "\t" "-g <hash> Check output from git hash\n"
	    "\t" "-s <rev>  Check output from svn revision\n"
	    "\t" "-t <tool> Launch external diff tool\n"
	    "\n"
	    "Examples:\n"
	    "\t" "indent_wrapper -D\n"
	    "\t" "indent_wrapper -D -t meld\n"
	    "\t" "indent_wrapper -D -t \"diff -u\"\n");
	exit(EX_SOFTWARE);
}