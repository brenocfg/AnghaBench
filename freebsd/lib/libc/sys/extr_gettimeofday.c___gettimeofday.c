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
struct timezone {int dummy; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int __sys_gettimeofday (struct timeval*,struct timezone*) ; 
 int __vdso_gettimeofday (struct timeval*,struct timezone*) ; 

int
__gettimeofday(struct timeval *tv, struct timezone *tz)
{
	int error;

	error = __vdso_gettimeofday(tv, tz);
	if (error == ENOSYS)
		error = __sys_gettimeofday(tv, tz);
	return (error);
}