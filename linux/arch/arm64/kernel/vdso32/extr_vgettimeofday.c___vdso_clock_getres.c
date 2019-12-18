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
typedef  scalar_t__ u32 ;
struct old_timespec32 {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ TASK_SIZE_32 ; 
 int __cvdso_clock_getres_time32 (int /*<<< orphan*/ ,struct old_timespec32*) ; 

int __vdso_clock_getres(clockid_t clock_id,
			struct old_timespec32 *res)
{
	/* The checks below are required for ABI consistency with arm */
	if ((u32)res >= TASK_SIZE_32)
		return -EFAULT;

	return __cvdso_clock_getres_time32(clock_id, res);
}