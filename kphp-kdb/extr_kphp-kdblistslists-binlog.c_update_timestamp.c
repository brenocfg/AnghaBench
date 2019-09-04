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
 int cur_timestamp ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int max_timestamp ; 
 int max_utime ; 
 int min_timestamp ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void update_timestamp (int timestamp) {
  cur_timestamp = timestamp;
  //avoid overlow (max_utime + 360 is illegal due int overlow)
  if (timestamp - 360 > max_utime) {
    if (verbosity >= 3) fprintf(stderr, "skiping binlog's tail\n");
    exit(0); /* skip binlog's tail (it doen't contains timestamp in given time range) */
  }

  if (min_timestamp > cur_timestamp) min_timestamp = cur_timestamp;
  if (max_timestamp < cur_timestamp) max_timestamp = cur_timestamp;
}