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
 int max_lru_size ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage (void) {
  printf ("%s\n", FullVersionStr);
  printf ("usage: [-v] [-p<port>] [-u<username>] [-M<max-memory-transactions>] [-b<backlog>] [-c<max-conn>] [-a<binlog-name>] [-l<log-name>] [-E] <binlog>\n"
	  "\tCollects transactions results from copyexec-engine.\n"
    "\t-E\tcreate copyexec-results empty binlog\n"
    "\t-M<max-memory-transactions>\tlimit memory transaction number (default value is %d).\n"
    "\t-v\toutput statistical and debug information into stderr\n", max_lru_size);
  exit (2);
}