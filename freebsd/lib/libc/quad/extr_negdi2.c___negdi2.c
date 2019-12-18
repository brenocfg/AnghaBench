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
union uu {int* ul; int /*<<< orphan*/  q; } ;
typedef  int /*<<< orphan*/  quad_t ;

/* Variables and functions */
 size_t H ; 
 size_t L ; 

quad_t
__negdi2(quad_t a)
{
	union uu aa, res;

	aa.q = a;
	res.ul[L] = -aa.ul[L];
	res.ul[H] = -aa.ul[H] - (res.ul[L] > 0);
	return (res.q);
}