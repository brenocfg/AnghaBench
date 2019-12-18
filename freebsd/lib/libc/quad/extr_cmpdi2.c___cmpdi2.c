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
union uu {scalar_t__* sl; scalar_t__* ul; void* q; } ;
typedef  void* quad_t ;

/* Variables and functions */
 size_t H ; 
 size_t L ; 

int
__cmpdi2(quad_t a, quad_t b)
{
	union uu aa, bb;

	aa.q = a;
	bb.q = b;
	return (aa.sl[H] < bb.sl[H] ? 0 : aa.sl[H] > bb.sl[H] ? 2 :
	    aa.ul[L] < bb.ul[L] ? 0 : aa.ul[L] > bb.ul[L] ? 2 : 1);
}