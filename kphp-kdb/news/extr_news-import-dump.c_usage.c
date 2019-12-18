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
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 

void usage (void) {
  printf ("usage: %s [-v] -m <log-split-mod> -n <import-file> [-o] [-x] <answer-file-prefix>\n"
	  "\tConverts dump of bookmarks database into news-engine binlog\n"
    "\t-o: Split by owner (default split by place)\n"
    "\t-x: Split by (owner xor place) (default by place)\n"
    "\t-z: Use txt file for import\n", progname);
  exit(2);
}