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
typedef  scalar_t__ u_quad_t ;
typedef  double quad_t ;

/* Variables and functions */
 double QUAD_MAX ; 
 double QUAD_MIN ; 

quad_t
__fixdfdi(double x)
{
	if (x < 0)
		if (x <= QUAD_MIN)
			return (QUAD_MIN);
		else
			return ((quad_t)-(u_quad_t)-x);
	else
		if (x >= QUAD_MAX)
			return (QUAD_MAX);
		else
			return ((quad_t)(u_quad_t)x);
}