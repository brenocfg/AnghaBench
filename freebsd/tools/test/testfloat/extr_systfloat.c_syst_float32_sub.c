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
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */

float32 syst_float32_sub( float32 a, float32 b )
{
    float32 z;

    *( (float *) &z ) = *( (float *) &a ) - *( (float *) &b );
    return z;

}