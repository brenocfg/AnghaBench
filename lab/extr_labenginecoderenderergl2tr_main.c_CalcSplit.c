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
 float pow (float,float) ; 

__attribute__((used)) static float CalcSplit(float n, float f, float i, float m)
{
	return (n * pow(f / n, i / m) + (f - n) * i / m) / 2.0f;
}