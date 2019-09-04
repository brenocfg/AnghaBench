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

__attribute__((used)) static float bezier( float x0, float x1, float x2, float x3, float t ){
	float a, b, c, t2, t3;

	t2 = t * t;
	t3 = t2 * t;

	c = 3.0f * ( x1 - x0 );
	b = 3.0f * ( x2 - x1 ) - c;
	a = x3 - x0 - c - b;

	return a * t3 + b * t2 + c * t + x0;
}