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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 int /*<<< orphan*/  rd_bytes ; 
 int /*<<< orphan*/  rd_rec ; 
 int /*<<< orphan*/  skipped_change_flags ; 
 int /*<<< orphan*/  skipped_change_value ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wr_bytes ; 
 int /*<<< orphan*/  wr_rec ; 

void output_stats (void) {
  fprintf (stderr,
	   "read: %lld bytes (reported binlog position %lld), %lld records\n"
	   "written: %lld bytes, %lld records\n",
	   rd_bytes, log_cur_pos(), rd_rec, wr_bytes, wr_rec);
  fprintf (stderr, "skipped_change_value: %lld bytes.\n", skipped_change_value);
  fprintf (stderr, "skipped_change_flags: %lld bytes.\n", skipped_change_flags);
}