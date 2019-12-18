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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage()
{
	fprintf(stderr,
	   "usage:  $s [ -c chdir ] [-d level] [-f configfile] [host...]\n");
	fprintf(stderr, "\t -c n\tset current directory\n");
	fprintf(stderr, "\t -d n\tset debug level\n");
	fprintf(stderr, "\t -f n\tconfig file name\n");
	exit(1);
}