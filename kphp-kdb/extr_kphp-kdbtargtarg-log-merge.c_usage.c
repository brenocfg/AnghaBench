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
  fprintf (stderr, "usage:\t%s [-v] [-u<username>] [-t<seconds-ago>] <old-binlog-file> [<new-binlog-file>] [<current-binlog-file>]\n"
	   "\tAppends targeting records to another binlog. "
	   "If <output-file> is specified, resulting binlog is appended to it.\n"
	   "\t-h\tthis help screen\n"
	   "\t-v\tverbose mode on\n"
	   "\t-t<seconds-ago>\tcopy all records created after given threshold\n"
	   "\t-u<username>\tassume identity of given user\n",
	   progname);
}