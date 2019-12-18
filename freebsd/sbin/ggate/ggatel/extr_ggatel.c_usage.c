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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr, "usage: %s create [-v] [-o <ro|wo|rw>] "
	    "[-s sectorsize] [-t timeout] [-u unit] <path>\n", getprogname());
	fprintf(stderr, "       %s rescue [-v] [-o <ro|wo|rw>] <-u unit> "
	    "<path>\n", getprogname());
	fprintf(stderr, "       %s destroy [-f] <-u unit>\n", getprogname());
	fprintf(stderr, "       %s list [-v] [-u unit]\n", getprogname());
	exit(EXIT_FAILURE);
}