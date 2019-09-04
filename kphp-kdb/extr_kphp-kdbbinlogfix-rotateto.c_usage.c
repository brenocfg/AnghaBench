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
 int /*<<< orphan*/  printf (char*,...) ; 

void usage (void) {
  printf ("%s\n", FullVersionStr);
  printf (
    "fix-rotateto [-u<username>] [-c<max-conn>] [-v] <src-binlog1> <src-binlog2> <dst-binlog1> \n"
    "\tTry to append ROTATE_TO logevent to <src-binlog1> using ROTATE_FROM logevent from <src-binlog2>.\n"
    "\tAfter running this tool always use check-binlog before deleting <src-binlog1>.\n"
    "\t[-v]\t\toutput statistical and debug information into stderr\n"
    "\t[-k]\t\tkeep <dst-binlog1> in case some error was occured.\n"
  );
  exit (2);
}