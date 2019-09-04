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
 char* full_version_str ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 

void usage (void) {
  printf ("%s\n", full_version_str);
  printf ("usage: %s [-v] [-r] [-i] [-p<port>] [-u<username>] [-b<backlog>] [-c<max-conn>] [-a<binlog-name>] [-B<max-binlog-size>] [-l<log-name>] [-d] [-W] <index-prefix>\n"
    "\tPerforms antispam patterns queries\n"
    "\t<index-prefix>\tprefix to generate name of index files\n"
    "\t              \tand binlog files (if there is no -a option)\n"
    "\t-h\tdisplay this message\n"
    "\t-v\toutput statistical and debug information into stderr\n"
    "\t  \t(type several times to increase verbosity level)\n"
    "\t-r\tread-only binlog (don't log new events)\n"
    "\t-i\tenable index mode (create index snapshot instead of running)\n"
    "\t-p<port>\tspecify where to open server socket (default 30303)\n"
    "\t-u<username>\tspecify process owner\n"
    "\t-c<max-conn>\tmaximum number of connection to this engine instance\n"
    "\t  \t(default: 1000/65536 depends on your permissions level)\n"
    "\t-a<binlog-name>\tspecify binlog to load from\n"
    "\t-B<max-binlog-size>\tdefines maximum size of each binlog file\n"
    "\t-l<log-name>\tspecify where to write stderr log\n"
    "\t-d\tenable daemonize mode\n"
    "\t-W\tflush binlog in main cycle\n",
    progname);
  exit (2);
}