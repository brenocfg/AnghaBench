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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */

__attribute__((used)) static void
rtld_cpuid_count(int idx, int cnt, u_int *p)
{

	__asm __volatile(
	    "	pushl	%%ebx\n"
	    "	cpuid\n"
	    "	movl	%%ebx,%1\n"
	    "	popl	%%ebx\n"
	    : "=a" (p[0]), "=r" (p[1]), "=c" (p[2]), "=d" (p[3])
	    :  "0" (idx), "2" (cnt));
}