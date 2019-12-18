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
 char* DRILL_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* ldns_version () ; 

__attribute__((used)) static void
version(FILE *stream, const char *progname)
{
        fprintf(stream, "%s version %s (ldns version %s)\n", progname, DRILL_VERSION, ldns_version());
        fprintf(stream, "Written by NLnet Labs.\n");
        fprintf(stream, "\nCopyright (c) 2004-2008 NLnet Labs.\n");
        fprintf(stream, "Licensed under the revised BSD license.\n");
        fprintf(stream, "There is NO warranty; not even for MERCHANTABILITY or FITNESS\n");
        fprintf(stream, "FOR A PARTICULAR PURPOSE.\n");
}