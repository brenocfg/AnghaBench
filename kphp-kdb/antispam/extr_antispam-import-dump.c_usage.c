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
  fprintf (stderr, "usage:\t%s [-h] [-v] [-u<username>] [-B<max-binlog-size>] [-p<patterns-dump-name>] [-c] <binlog-name>\n"
           "\tConverts tab-separated table dump into KDB binlog (for antispam-engine).\n"
           "\tRecommented mySQL query: \"SELECT * FROM recent_patterns WHERE state >= 0 AND conditions = ''\"\n"
           "\t-h\tthis help screen\n"
           "\t-v\tverbose mode on\n"
           "\t-c\tclears <binlog-name> before dump appending (setup empty binlog)\n"
           "\t-u<username>\tassume identity of given user\n"
           "\t-B<max-binlog-size>\tdefines maximum size of each binlog file\n"
           "\t-p<patterns-dump-name>\tif specified will be appended to the <binlog-name> tail\n"
           "\t                      \tdump line format: id<tab>ip<tab>ua_hash<tab>flags<tab>pattern\n"
           "\t                      \tflags & 0|32|16 (means simplify-type=none|partial|full)\n"
           "\t<binlog-name>\tspecify binlog to replay and append patterns dump\n",
           progname);
}