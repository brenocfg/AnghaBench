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
 char* FullVersionStr ; 
 int /*<<< orphan*/  exit (int) ; 
 int lss_threshold ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* progname ; 

void usage (void) {
  printf ("%s\n", FullVersionStr);
  printf ("usage: %s [-v] [-t] [-A] [-u<username>] [-a<binlog-name>] [-l<log-name>] [-f] <huge-index-file>\n"
      "\tBuilds a search index from given binlog file.\n"
      "\t-t\tenable tags (*word @word #word are considered words)\n"
      "\t-A\tenable universal tag\n"
      "\t-S\tuse stemmer\n"
      "\t-U\tenable UTF-8 mode\n"
      "\t-D\tstore in item's date modification time (default: first creation time)\n"
      "\t-H<heap-size>\tsets maximal heap size, e.g. 4g\n"
      "\t-B<heap-size>\tsets maximal binlog size, e.g. 4g\n"
      "\t-P<max_pairs>\tsets maximal number of pairs\n"
      "\t-v\toutput statistical and debug information into stderr\n"
      "\t-O\tenable tag owner mode\n"
      "\t-x<left subtree size threshold>\tdefault (-x '%d')\n"
      , progname, lss_threshold
    );
  exit (2);
}