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
 int /*<<< orphan*/  parse_usage () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 

void usage (void) {
  printf ("%s\n", FullVersionStr);
  printf ("usage: %s [-v] [-r] [-i] [-p<port>] [-u<username>] [-b<backlog>] [-c<max-conn>] [-a<binlog-name>] [-l<log-name>] [-A] <huge-index-file> [<metaindex-file>]\n"
	  "\tPerforms friends and privacy queries using given indexes\n",
	  progname);
  parse_usage ();
  exit (2);
}