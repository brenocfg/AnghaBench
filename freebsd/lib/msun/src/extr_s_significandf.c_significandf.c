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
 float __ieee754_scalbf (float,float) ; 
 scalar_t__ ilogbf (float) ; 

float
significandf(float x)
{
	return __ieee754_scalbf(x,(float) -ilogbf(x));
}