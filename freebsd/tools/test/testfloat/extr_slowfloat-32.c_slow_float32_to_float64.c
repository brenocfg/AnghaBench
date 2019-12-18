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
typedef  int /*<<< orphan*/  float64 ;
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */
 int /*<<< orphan*/  float32ToFloatX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floatXToFloat64 (int /*<<< orphan*/ ) ; 

float64 slow_float32_to_float64( float32 a )
{

    return floatXToFloat64( float32ToFloatX( a ) );

}