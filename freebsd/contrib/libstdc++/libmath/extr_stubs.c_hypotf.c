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
 float fabsf (float) ; 
 float sqrtf (float) ; 

float
hypotf(float x, float y)
{
  float s = fabsf(x) + fabsf(y);
  if (s == 0.0F)
    return s;
  x /= s; y /= s;
  return s * sqrtf(x * x + y * y);
}