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
		"usage: bootpgw [-a] [-i | -s] [-d level] [-h count] [-t timeout]\n"
		"               [-w time] server\n");
	fprintf(stderr, "\t -a\tdon't modify ARP table\n");
	fprintf(stderr, "\t -d n\tset debug level\n");
	fprintf(stderr, "\t -h n\tset max hop count\n");
	fprintf(stderr, "\t -i\tforce inetd mode (run as child of inetd)\n");
	fprintf(stderr, "\t -s\tforce standalone mode (run without inetd)\n");
	fprintf(stderr, "\t -t n\tset inetd exit timeout to n minutes\n");
	fprintf(stderr, "\t -w n\tset min wait time (secs)\n");
	exit(1);
}