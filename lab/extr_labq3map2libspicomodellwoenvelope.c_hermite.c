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

__attribute__((used)) static void hermite( float t, float *h1, float *h2, float *h3, float *h4 ){
	float t2, t3;

	t2 = t * t;
	t3 = t * t2;

	*h2 = 3.0f * t2 - t3 - t3;
	*h1 = 1.0f - *h2;
	*h4 = t3 - t2;
	*h3 = *h4 - t2 + t;
}