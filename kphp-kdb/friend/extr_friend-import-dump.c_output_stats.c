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
 scalar_t__ GC ; 
 scalar_t__ GS ; 
 int /*<<< orphan*/  Gc ; 
 int /*<<< orphan*/  Gd ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  ext_lists_output ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int line_no ; 
 int /*<<< orphan*/  lists_output ; 
 int rd_bytes ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wr_bytes ; 

void output_stats (void) {
  fprintf (stderr,
	   "read: %lld bytes, %d records read, %d processed\n"
	   "written: %lld bytes\n"
	   "temp data: %ld bytes allocated, %d+%d in read/write maps\n"
	   "lists output: %d basic, %d extended\n",
	   rd_bytes, line_no, adj_rec, wr_bytes, (long)(GS - GC), Gc, Gd,
	   lists_output, ext_lists_output);
}