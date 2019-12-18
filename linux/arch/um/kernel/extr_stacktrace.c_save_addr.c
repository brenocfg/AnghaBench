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
struct stack_trace {scalar_t__ nr_entries; scalar_t__ max_entries; unsigned long* entries; } ;

/* Variables and functions */

__attribute__((used)) static void save_addr(void *data, unsigned long address, int reliable)
{
	struct stack_trace *trace = data;

	if (!reliable)
		return;
	if (trace->nr_entries >= trace->max_entries)
		return;

	trace->entries[trace->nr_entries++] = address;
}