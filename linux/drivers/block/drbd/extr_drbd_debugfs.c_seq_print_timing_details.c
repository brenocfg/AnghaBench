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
struct seq_file {int dummy; } ;
struct drbd_thread_timing_details {int dummy; } ;

/* Variables and functions */
 unsigned int DRBD_THREAD_DETAILS_HIST ; 
 int /*<<< orphan*/  seq_print_one_timing_detail (struct seq_file*,struct drbd_thread_timing_details*,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*) ; 

__attribute__((used)) static void seq_print_timing_details(struct seq_file *m,
		const char *title,
		unsigned int cb_nr, struct drbd_thread_timing_details *tdp, unsigned long now)
{
	unsigned int start_idx;
	unsigned int i;

	seq_printf(m, "%s\n", title);
	/* If not much is going on, this will result in natural ordering.
	 * If it is very busy, we will possibly skip events, or even see wrap
	 * arounds, which could only be avoided with locking.
	 */
	start_idx = cb_nr % DRBD_THREAD_DETAILS_HIST;
	for (i = start_idx; i < DRBD_THREAD_DETAILS_HIST; i++)
		seq_print_one_timing_detail(m, tdp+i, now);
	for (i = 0; i < start_idx; i++)
		seq_print_one_timing_detail(m, tdp+i, now);
}