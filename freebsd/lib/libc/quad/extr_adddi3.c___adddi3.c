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
union uu {void* q; scalar_t__* ul; } ;
typedef  void* quad_t ;

/* Variables and functions */
 size_t H ; 
 size_t L ; 

quad_t
__adddi3(quad_t a, quad_t b)
{
	union uu aa, bb, sum;

	aa.q = a;
	bb.q = b;
	sum.ul[L] = aa.ul[L] + bb.ul[L];
	sum.ul[H] = aa.ul[H] + bb.ul[H] + (sum.ul[L] < bb.ul[L]);
	return (sum.q);
}