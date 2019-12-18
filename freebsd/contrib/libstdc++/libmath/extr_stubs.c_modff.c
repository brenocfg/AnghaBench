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
 double modf (float,double*) ; 

float
modff(float x, float *iptr)
{
  double result, temp;

  result = modf(x, &temp);
  *iptr = (float) temp;
  return (float) result;
}