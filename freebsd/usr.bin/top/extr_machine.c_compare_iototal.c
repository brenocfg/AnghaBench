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
 int get_io_total (struct kinfo_proc const* const) ; 

__attribute__((used)) static int
compare_iototal(const void *arg1, const void *arg2)
{
	const struct kinfo_proc * const p1 = *(const struct kinfo_proc * const *)arg1;
	const struct kinfo_proc * const p2 = *(const struct kinfo_proc * const *)arg2;

	return (get_io_total(p2) - get_io_total(p1));
}