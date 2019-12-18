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
struct __kernel_timespec {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int __cvdso_clock_getres (int /*<<< orphan*/ ,struct __kernel_timespec*) ; 

int __kernel_clock_getres(clockid_t clock_id,
			  struct __kernel_timespec *res)
{
	return __cvdso_clock_getres(clock_id, res);
}