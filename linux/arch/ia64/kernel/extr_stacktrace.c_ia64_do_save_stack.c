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
struct unw_frame_info {int dummy; } ;
struct stack_trace {int skip; scalar_t__ nr_entries; unsigned long* entries; scalar_t__ max_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  unw_get_ip (struct unw_frame_info*,unsigned long*) ; 
 scalar_t__ unw_unwind (struct unw_frame_info*) ; 

__attribute__((used)) static void
ia64_do_save_stack(struct unw_frame_info *info, void *arg)
{
	struct stack_trace *trace = arg;
	unsigned long ip;
	int skip = trace->skip;

	trace->nr_entries = 0;
	do {
		unw_get_ip(info, &ip);
		if (ip == 0)
			break;
		if (skip == 0) {
			trace->entries[trace->nr_entries++] = ip;
			if (trace->nr_entries == trace->max_entries)
				break;
		} else
			skip--;
	} while (unw_unwind(info) >= 0);
}