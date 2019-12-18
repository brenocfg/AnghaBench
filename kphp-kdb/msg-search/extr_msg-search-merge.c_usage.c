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
  printf ("usage: %s [-v] [-u<username>] [-c<cutoff-seconds>] [-a<binlog-suffix>] [-i<metaindex-suffix>] <old-huge-index-file> <new-huge-index-file>\n"
	  "\tCombines <old-huge-index-file> with corresponding binlog, obtained by appending <binlog-suffix> to <old-huge-index-file>, into <new-huge-index-file>, generating corresponding new binlog and metaindex files\n"
	  "\t-v\toutput statistical and debug information into stderr\n"
	  "\t-u<username>\tassume identity of specified user (if invoked with root privileges)\n"
	  "\t-c<cutoff-seconds>\tscan old binlog until <cutoff-seconds> ago, after that point process only undeletion operations (3600)\n"
	  "\t-a<binlog-suffix>\tsuffix used to obtain binlog filename from huge index filename (.bin)\n"
	  "\t-i<metaindex-suffix>\tsuffix used to obtain metaindex filename (.idx)\n",
	  progname);
  exit(2);
}