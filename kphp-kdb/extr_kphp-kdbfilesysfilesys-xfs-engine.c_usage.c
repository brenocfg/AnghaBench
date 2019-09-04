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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void usage (void) {
  fprintf (stderr, "%s\n", FullVersionStr);
  fprintf (stderr,
           "./filesys-xfs-engine [-v] [-i] [-x] [-O] [-p<port>] [-u<username>] [-b<backlog>] [-c<max-conn>] [-a<binlog-name>] [-l<log-name>] <extract-dir> <binlog>\n"
                   "\t-v\tincrease verbosity level\n"
                   "\t-H<heap-size>\tsets maximal zmalloc heap size, e.g. 4g\n"
                   "\t-1\tcompress snapshot faster\n"
                   "\t-9\tcompress snapshot better (default)\n"
                   "\t-O\tchange <extract-dir> permissions to 0700 for index loading & log replaying\n"
                   "\t-i\textract sources, create index and exit\n"
                   "\t-x\textract sources and exit\n"
                   "\n"
                   "\t\tOn startup, extract-dir should be empty or contain .binlogpos file.\n"
                   "\t\t.binlogpos is unlinked just before processing any filesys-xfs logevent.\n"
                   "\t\t.binlogpos file is created after exit (SIGTERM, SIGINT), after end of transaction (case no other logevents) or before creating snapshot.\n");
  exit (2);
}