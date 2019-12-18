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

/* Variables and functions */
 long long __divdi3 (long long,long long) ; 

long long
__kern_ldivmod(long long n, long long m, long long *rem)
{
	long long q;

	q = __divdi3(n, m);	/* q = n / m */
	*rem = n - m * q;

	return q;
}