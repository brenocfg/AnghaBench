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
 char* SDP_LOCAL_PATH ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
"Usage: sdpcontrol options command\n" \
"Where options are:\n"
"	-a address	address to connect to\n" \
"	-c path		path to the control socket (default is %s)\n" \
"	-h		display usage and quit\n" \
"	-l		connect to the local SDP server via control socket\n" \
"	command		one of the supported commands\n", SDP_LOCAL_PATH);
	exit(255);
}