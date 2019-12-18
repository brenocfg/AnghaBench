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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  parse_usage () ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void usage (void) {
  fprintf (stderr, "usage: %s [-u<username>] [-v] [-d] [-6] [-l<log-name>] (<dir> | <input> <output>)\n%s\n"
    "Trivial file transfer protocol tool.\n"
    "If <dir> is given then tool works as server.\n"
    "Otherwise tool works as client.\n"
    , progname, FullVersionStr);
  parse_usage ();
  exit (2);
}