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
struct pvclock_vsyscall_time_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hv_clock_per_cpu ; 
 struct pvclock_vsyscall_time_info* this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct pvclock_vsyscall_time_info *this_cpu_hvclock(void)
{
	return this_cpu_read(hv_clock_per_cpu);
}