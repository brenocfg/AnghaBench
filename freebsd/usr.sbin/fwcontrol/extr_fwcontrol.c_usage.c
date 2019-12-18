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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
		"%s [-u bus_num] [-prt] [-c node] [-d node] [-o node] [-s node]\n"
		"\t  [-l file] [-g gap_count] [-f force_root ] [-b pri_req]\n"
		"\t  [-M mode] [-R filename] [-S filename] [-m EUI64 | hostname]\n"
		"\t-u: specify bus number\n"
		"\t-p: Display current PHY register settings\n"
		"\t-r: bus reset\n"
		"\t-t: read topology map\n"
		"\t-c: read configuration ROM\n"
		"\t-d: hex dump of configuration ROM\n"
		"\t-o: send link-on packet to the node\n"
		"\t-s: write RESET_START register on the node\n"
		"\t-l: load and parse hex dump file of configuration ROM\n"
		"\t-g: set gap count\n"
		"\t-f: force root node\n"
		"\t-b: set PRIORITY_BUDGET register on all supported nodes\n"
		"\t-M: specify dv or mpeg\n"
		"\t-R: Receive DV or MPEG TS stream\n"
		"\t-S: Send DV stream\n"
		"\t-m: set fwmem target\n"
		, getprogname() );
	fprintf(stderr, "\n");
}