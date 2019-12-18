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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void usage() {
  fprintf (stderr, "text-binlog [-p] [-t] [-v] [-h] [-S<start-time>] [-T<end-time] <binlog>\n"
                   "\tConverts text into text format.\n"
                   "\tUnfinished version (only LEV_TX_INCR_MESSAGE_FLAGS logevents).\n"
                   "\t-p\tdump log pos\n"
                   "\t-t\tdump timestamp\n"
                   "\t-C\tdump CRC32\n"
                   "\t-S<start-time>\tsets start-time\n"
                   "\t-T<end-time>\tsets end-time\n");
  exit (2);
}