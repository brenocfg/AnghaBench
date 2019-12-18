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
  fprintf (stderr, "usage:\t%s [-v] [-u<username>] [-m<rem>,<mod>] <old-binlog-file> [<output-file>]\n"
	   "\tCopies (some of) targeting engine binlog records to another binlog. "
	   "If <output-file> is specified, resulting binlog is appended to it.\n"
	   "\t-h\tthis help screen\n"
	   "\t-v\tverbose mode on\n"
           "\t-f\tskip LEV_ROTATE_TO and LEV_ROTATE_FROM entries (useful when binlog is merged in one file)\n"
	   "\t-m<rem>,<mod>\tcopy only record with id %% <mod> == <rem>\n"
	   "\t-q<split-quotient>\tnumber of new binlogs made from one old\n"
	   "\t-s<start-binlog-pos>\tstart reading binlog from specified position\n"
	   "\t-t<stop-binlog-pos>\tstop reading binlog at specified position\n"
	   "\t-u<username>\tassume identity of given user\n",
	   progname);
}