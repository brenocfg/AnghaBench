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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void usage()
{
	fprintf(stderr, "usage: %s [-nv] -l\n", progname);
	fprintf(stderr, "usage: %s [-nv] -u\n", progname);
	fprintf(stderr, "usage: %s [-nv] [-d <dir>] -R\n", progname);
	fprintf(stderr, "usage: %s [-nv] [-d <dir>] -W\n", progname);
	fprintf(stderr, "usage: %s [-nNSv] [-f <file>] -r\n", progname);
	fprintf(stderr, "usage: %s [-nNSv] [-f <file>] -w\n", progname);
	fprintf(stderr, "usage: %s [-nNSv] -f <filename> -i <if1>,<if2>\n",
		progname);
	exit(1);
}