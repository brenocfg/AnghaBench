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
  fprintf (stderr, "usage:\t%s [-v] [-n] [-t<days>] [-u<username>] [-m<rem>,<mod>] [-g<filename>] [-f<format>] [-o<output-class>] <input-file> [<output-file>]\n"
	   "\tConverts tab-separated table dump into KDB binlog. "
	   "If <output-file> is specified, resulting binlog is appended to it.\n"
	   "\t-h\tthis help screen\n"
	   "\t-v\tverbose mode on\n"
	   "\t-u<username>\tassume identity of given user\n"
	   "\t-g<filename>\tloads auxiliary data from given file\n"
	   "\t-m<rem>,<mod>\tslice parameters: consider only objects with id %% mod == rem\n"
	   "\t-n\tindex objects with negative ids\n"
	   "\t-t<days>\tmark old messages read\n"
	   "\t-o<int>\tdetermines output format\n"
	   "\t-f<format>\tdetermines dump format, one of inbox, outbox, minifeed, wall, ...\n",
	   progname);
}