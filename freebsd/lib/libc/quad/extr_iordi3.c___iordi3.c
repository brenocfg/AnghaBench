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
union uu {void* q; int /*<<< orphan*/ * ul; } ;
typedef  void* quad_t ;

/* Variables and functions */

quad_t
__iordi3(quad_t a, quad_t b)
{
	union uu aa, bb;

	aa.q = a;
	bb.q = b;
	aa.ul[0] |= bb.ul[0];
	aa.ul[1] |= bb.ul[1];
	return (aa.q);
}