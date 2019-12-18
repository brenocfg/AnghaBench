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
 int /*<<< orphan*/  Fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* prog ; 
 int /*<<< orphan*/  stderr ; 

void
usage(void)
{
	extern char version[];

	Fprintf(stderr, "Version %s\n", version);
	Fprintf(stderr,
	    "Usage: %s [-adDeFInrSvx] [-f first_ttl] [-g gateway] [-i iface]\n"
	    "\t[-m max_ttl] [-p port] [-P proto] [-q nqueries] [-s src_addr]\n"
	    "\t[-t tos] [-w waittime] [-A as_server] [-z pausemsecs] host [packetlen]\n", prog);
	exit(1);
}