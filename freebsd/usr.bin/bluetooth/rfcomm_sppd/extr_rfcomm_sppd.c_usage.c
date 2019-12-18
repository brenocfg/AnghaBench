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
 char* SPPD_IDENT ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stdout,
"Usage: %s options\n" \
"Where options are:\n" \
"\t-a address Peer address (required in client mode)\n" \
"\t-b         Run in background\n" \
"\t-c channel RFCOMM channel to connect to or listen on\n" \
"\t-t         use slave pseudo tty (required in background mode)\n" \
"\t-S         Server mode\n" \
"\t-h         Display this message\n", SPPD_IDENT);
	exit(255);
}