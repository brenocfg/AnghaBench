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
struct kinfo_proc {int dummy; } ;

/* Variables and functions */
 long get_io_stats (struct kinfo_proc const*,long*,long*,long*,long*,long*) ; 

__attribute__((used)) static long
get_io_total(const struct kinfo_proc *pp)
{
	long dummy;

	return (get_io_stats(pp, &dummy, &dummy, &dummy, &dummy, &dummy));
}