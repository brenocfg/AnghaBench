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
typedef  float int32 ;
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */

float32 syst_int32_to_float32( int32 a )
{
    float32 z;

    *( (float *) &z ) = a;
    return z;

}