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
 char* RFCOMM_PPPD ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stdout,
"Usage: %s options\n" \
"Where options are:\n" \
"\t-a address   Address to listen on or connect to (required for client)\n" \
"\t-c           Act as a clinet (default)\n" \
"\t-C channel   RFCOMM channel to listen on or connect to (required)\n" \
"\t-d           Run in foreground\n" \
"\t-D           Register Dial-Up Networking service (server mode only)\n" \
"\t-l label     Use PPP label (required)\n" \
"\t-s           Act as a server\n" \
"\t-S           Register Serial Port service (server mode only)\n" \
"\t-u N         Tell PPP to operate on /dev/tunN (client mode only)\n" \
"\t-h           Display this message\n", RFCOMM_PPPD);

	exit(255);
}