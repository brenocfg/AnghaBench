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
  fprintf (stderr, "./filesys-commit-changes [-v] [-t] [-T<temp-dir>] [-P] <master-dir> <new-dir> <binlog>\n"
                   "\t-0\tno gzip compression\n"
                   "\t-9\thighest gzip compression level\n"
                   "\t-P\tdisable diff/patch\n"
                   "\t-v\tincrease verbosity level\n"
                   "\t-t\tonly show diff, nothing append to binlog\n"
                   "\t-C\tuse cloning for synchronization master-dir (slower, but safer)\n"
                   "\t-T<temp-dir>\tshould be in the same filesystem as <master-dir>, by default is equal to <master-dir>/..\n"
                   "\t-U\tunlink previous fake snapshot\n"
         );
  exit (2);
}