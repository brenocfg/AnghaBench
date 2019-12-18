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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int ENOSYS ; 
 int __sys_clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int __vdso_clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/ * __vdso_gettc ; 

int
__clock_gettime(clockid_t clock_id, struct timespec *ts)
{
	int error;

	if (__vdso_clock_gettime != NULL && __vdso_gettc != NULL)
		error = __vdso_clock_gettime(clock_id, ts);
	else
		error = ENOSYS;
	if (error == ENOSYS)
		error = __sys_clock_gettime(clock_id, ts);
	return (error);
}