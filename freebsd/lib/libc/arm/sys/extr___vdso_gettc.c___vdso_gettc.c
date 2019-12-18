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
typedef  scalar_t__ u_int ;
struct vdso_timehands {scalar_t__ th_algo; scalar_t__ th_physical; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ VDSO_TH_ALGO_ARM_GENTIM ; 
 scalar_t__ cp15_cntpct_get () ; 
 scalar_t__ cp15_cntvct_get () ; 

int
__vdso_gettc(const struct vdso_timehands *th, u_int *tc)
{

	if (th->th_algo != VDSO_TH_ALGO_ARM_GENTIM)
		return (ENOSYS);
#if __ARM_ARCH >= 6
	/*
	 * Userspace gettimeofday() is only enabled on ARMv7 CPUs, but
	 * libc is compiled for ARMv6.  Due to clang issues, .arch
	 * armv7-a directive does not work.
	 */
	__asm __volatile(".word\t0xf57ff06f" : : : "memory"); /* isb */
	*tc = th->th_physical == 0 ? cp15_cntvct_get() : cp15_cntpct_get();
	return (0);
#else
	*tc = 0;
	return (ENOSYS);
#endif
}