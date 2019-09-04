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
  printf ("usage: %s [-v] [-d] [-r] [-p<port>] [-u<username>] [-b<backlog>] [-c<max-conn>] [-l<log-name>] <kfs-binlog-name>\n"
	  "\tPerforms generic RPC server/client operations\n"
	  "\t-v\toutput statistical and debug information into stderr\n"
	  "\t-r\tread-only binlog (don't log new events)\n",
	  progname ? progname : "SOMETHING");
  exit(2);
}