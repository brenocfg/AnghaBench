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
typedef  int /*<<< orphan*/  u_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  __qdivrem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u_quad_t
__umoddi3(u_quad_t a, u_quad_t b)
{
	u_quad_t r;

	(void)__qdivrem(a, b, &r);
	return (r);
}