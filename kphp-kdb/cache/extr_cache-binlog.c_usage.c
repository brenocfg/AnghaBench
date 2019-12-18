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
  fprintf (stderr,
    "cache-binlog [-p] [-t] [-v] <cache-binlog>\n"
    "\tRead cache binlog and dumps logevents.\n"
    "\t-F<filtered-uri-hex-md5>\tsets global URI's md5 which will be dumped\n"
    "\t-p\tdump log pos\n"
    "\t-t\tdump timestamp\n"
  );
  exit (2);
}