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
 int interpolative_percent ; 
 int /*<<< orphan*/  lss_threshold ; 
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
	  "\t-W\tenable storing words frequencies in item\n"
    "\t-D\tstore in item's date modification time (default: first creation time)\n"
    "\t-H<heap-size>\tsets maximal heap size, e.g. 4g\n"
    "\t-B<heap-size>\tsets maximal binlog size, e.g. 4g\n"
    "\t-P<max_pairs>\tsets maximal number of pairs\n"
    "\t-v\toutput statistical and debug information into stderr\n"
    "\t-f\tallow to load snapshots without crc32\n"
    "\t-O\tenable tag owner mode\n"
#ifndef SEARCHX
    "\t-Q\toutput hash stats\n"
    "\t-0\tuse only Golomb coding (faster decompression)\n"
    "\t-1\tuse Interpolative coding (slower decompression)\n"
    "\t\t\tif it consumes less than %.6lf%% memory used by Golomb coding\n"
    "\t-2\tuse Interpolative coding if it consumes less memory than Golomb coding\n"
    "\t-x<left subtree size threshold>\tuse Redundant Interpolative coding.\n"
    "\t by default -x%d compression is used.\n"
    "\t-I<filename>\toutput to the given text file all item_ids and exit without saving index\n"
#endif
	  , progname
#ifndef SEARCHX
    , interpolative_percent, lss_threshold
#endif
    );
  exit (2);
}