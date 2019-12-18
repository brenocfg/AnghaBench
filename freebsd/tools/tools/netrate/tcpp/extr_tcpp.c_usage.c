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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr, "client: tcpp"
	    " -c remoteIP"
	    " [-h]"
	    " [-P]"
	    " [-M localIPcount]"
	    " [-l localIPbase]"
	    "\n\t"
	    " [-b bytespertcp]"
	    " [-m maxtcpsatonce]"
	    " [-p procs]"
	    " [-t tcpsperproc]"
	    "\n"
	    "\t"
	    " [-r baseport]"
	    "\n");

	fprintf(stderr, "server: tcpp"
	    " -s"
	    " [-P]"
	    " [-l localIPbase]"
	    " [-m maxtcpsatonce]"
	    " [-p procs]"
	    "\n"
	    "\t"
	    " [-r baseport]"
	    "\n");
	exit(EX_USAGE);
}