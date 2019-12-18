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
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */
 int /*<<< orphan*/  floatXToFloat32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int32ToFloatX (int /*<<< orphan*/ ) ; 

float32 slow_int32_to_float32( int32 a )
{

    return floatXToFloat32( int32ToFloatX( a ) );

}