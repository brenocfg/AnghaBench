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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void usage (void) {
  fprintf (stderr, "usage:\t%s [-v] [-u<username>] [-m<rem>,<mod>] [-g<map-file>] <old-binlog-file> [<output-binlog-file>]\n"
	   "\tCopies (some of) text engine binlog records to another binlog. "
	   "If <output-file> is specified, resulting binlog is appended to it.\n"
	   "\t-h\tthis help screen\n"
	   "\t-v\tverbose mode on\n"
	   "\t-g<map-file>\tload file with user names\n"
	   "\t-m<rem>,<mod>\tcopy only record with id %% <mod> == <rem>\n"
	   "\t-s<start-binlog-pos>\tstart reading binlog from specified position\n"
	   "\t-t<stop-binlog-pos>\tstop reading binlog at specified position\n"
	   "\t-u<username>\tassume identity of given user\n",
	   progname);
}