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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 int /*<<< orphan*/  rd_bytes ; 
 int /*<<< orphan*/  rd_rec ; 
 int /*<<< orphan*/  rd_views_rec ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wr_bytes ; 
 int /*<<< orphan*/  wr_rec ; 
 int /*<<< orphan*/  wr_views_rec ; 

void output_stats (void) {
  fprintf (stderr,
	   "read: %lld bytes (reported binlog position %lld), %lld records, out of them %lld ad_view\n"
	   "written: %lld bytes, %lld records, out of them %lld ad_view\n",
	   rd_bytes, log_cur_pos(), rd_rec, rd_views_rec, wr_bytes, wr_rec, wr_views_rec);
}