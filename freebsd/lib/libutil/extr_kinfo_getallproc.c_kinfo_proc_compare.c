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
struct kinfo_proc {int ki_pid; int ki_tid; } ;

/* Variables and functions */

__attribute__((used)) static int
kinfo_proc_compare(const void *a, const void *b)
{
	int i;

	i = ((const struct kinfo_proc *)a)->ki_pid -
	    ((const struct kinfo_proc *)b)->ki_pid;
	if (i != 0)
		return (i);
	i = ((const struct kinfo_proc *)a)->ki_tid -
	    ((const struct kinfo_proc *)b)->ki_tid;
	return (i);
}