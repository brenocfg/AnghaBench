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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void usage (void) {
  fprintf (stderr, "usage:\t%s <binlog-file>\n"
                   "\tConverts lists binlog into text format.\n"
                   "\tflags:\n"
                   "\t-t<min_utime,max_utime>\tset dumping range, unix times should separated by single comma\n"
                   "\t-r<seconds-ago>\n"
                   "\t-a\tdump timestamp in human readable format\n"
   ,progname);
}