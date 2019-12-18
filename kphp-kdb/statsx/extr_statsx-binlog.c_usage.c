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
  fprintf (stderr, "Debug utils: read stats binlog and dumps events for given counter.\n");
  fprintf (stderr, "\t-c [counter_id]\tDumps only logevent for given counter.\n");
  fprintf (stderr, "\t-l\tGenerate list of all used counters\n");
  fprintf (stderr, "\t-u\tGenerate list of active users (finding bots)\n");
  fprintf (stderr, "\t-S<start time>\n");
  fprintf (stderr, "\t-T<end time>\n");
  fprintf (stderr, "\t-i\tuse recent snapshot (for the case when first binlog was deleted)\n");
  exit (2);
}