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
 int DEFAULT_PAYLOAD_SIZE ; 
 int DEFAULT_PORT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int IPPROTO_ZEROHOP ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr, "IPv4 broadcast test program. Sends a %d byte UDP "
	        "datagram to <dest>:<port>.\n\n", DEFAULT_PAYLOAD_SIZE);
	fprintf(stderr,
"usage: %s [-1] [-A laddr] [-b] [-B] [-d] [-i iface] [-l len]\n"
"                   [-p port] [-R] [-s srcaddr] [-t ttl] <dest>\n",
	    progname);
	fprintf(stderr, "-1: Set IP_ONESBCAST\n");
	fprintf(stderr, "-A: specify laddr (default: INADDR_ANY)\n");
	fprintf(stderr, "-b: bind socket to <laddr>:<lport>\n");
	fprintf(stderr, "-B: Set SO_BROADCAST\n");
	fprintf(stderr, "-d: Set SO_DONTROUTE\n");
	fprintf(stderr, "-i: Set IP_SENDIF <iface> (if supported)\n");
	fprintf(stderr, "-l: Set payload size to <len>\n");
	fprintf(stderr, "-p: Set local and remote port (default: %d)\n",
	    DEFAULT_PORT);
	fprintf(stderr, "-R: Use raw IP (protocol %d)\n", IPPROTO_ZEROHOP);
#if 0
	fprintf(stderr, "-r: Fill datagram with random bytes\n");
#endif
	fprintf(stderr, "-s: Set IP_SENDSRCADDR to <srcaddr>\n");
	fprintf(stderr, "-t: Set IP_TTL to <ttl>\n");

	exit(EXIT_FAILURE);
}