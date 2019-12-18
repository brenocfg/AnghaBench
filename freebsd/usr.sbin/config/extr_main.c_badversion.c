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
 int CONFIGVERS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int versreq ; 

__attribute__((used)) static void
badversion(void)
{
	fprintf(stderr, "ERROR: version of config(8) does not match kernel!\n");
	fprintf(stderr, "config version = %d, ", CONFIGVERS);
	fprintf(stderr, "version required = %d\n\n", versreq);
	fprintf(stderr, "Make sure that /usr/src/usr.sbin/config is in sync\n");
	fprintf(stderr, "with your /usr/src/sys and install a new config binary\n");
	fprintf(stderr, "before trying this again.\n\n");
	fprintf(stderr, "If running the new config fails check your config\n");
	fprintf(stderr, "file against the GENERIC or LINT config files for\n");
	fprintf(stderr, "changes in config syntax, or option/device naming\n");
	fprintf(stderr, "conventions\n\n");
	exit(1);
}