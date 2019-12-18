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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* prog ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
"\n"
"usage:\n"
"    %s [-dr] [-b maxbytes] [-p maxpkts] [-P pidfile] portnum dumpfile\n"
"\n"
"where:\n"
"	'-d'  = enable debugging messages.\n"
"	'-r'  = reflect. write packets back to the divert socket.\n"
"		(ie. simulate the original intent of \"ipfw tee\").\n"
"	'-rr' = indicate that it is okay to quit if packet-count or\n"
"		byte-count limits are reached (see the NOTE below\n"
"		about what this implies).\n"
"	'-b bytcnt'   = stop dumping after {bytcnt} bytes.\n"
"	'-p pktcnt'   = stop dumping after {pktcnt} packets.\n"
"	'-P pidfile'  = alternate file to store the PID\n"
"			(default: /var/run/%s.{portnum}.pid).\n"
"\n"
"	portnum  = divert(4) socket port number.\n"
"	dumpfile = file to write captured packets (tcpdump format).\n"
"		   (specify '-' to write packets to stdout).\n"
"\n"
"The '-r' option should not be necessary, but because \"ipfw tee\" is broken\n"
"(see BUGS in ipfw(8) for details) this feature can be used along with\n"
"an \"ipfw divert\" rule to simulate the original intent of \"ipfw tee\".\n"
"\n"
"NOTE: With an \"ipfw divert\" rule, diverted packets will silently\n"
"      disappear if there is nothing listening to the divert socket.\n"
"\n", prog, prog);
	exit(1);
}