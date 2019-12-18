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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  float64 ;

/* Variables and functions */
 int /*<<< orphan*/  floatXToFloat64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int32ToFloatX (int /*<<< orphan*/ ) ; 

float64 slow_int32_to_float64( int32 a )
{

    return floatXToFloat64( int32ToFloatX( a ) );

}