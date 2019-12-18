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
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void usage (void) {
  fprintf (stderr, "usage: %s [-u<username>] [-v] [-l<log-name>] <new-binlog> <old-binlog> %s\n"
    "Appends <old-binlog> so it will be identical to <new-binlog>.\n"
    "<new-binlog> should be generated with dns-engine via -E option.\n"
    , progname, FullVersionStr);
  exit (2);
}