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
typedef  int float32 ;

/* Variables and functions */
 int /*<<< orphan*/  float32ToFloatX (int) ; 
 int /*<<< orphan*/  floatXAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int floatXToFloat32 (int /*<<< orphan*/ ) ; 

float32 slow_float32_sub( float32 a, float32 b )
{

    b ^= 0x80000000;
    return
        floatXToFloat32(
            floatXAdd( float32ToFloatX( a ), float32ToFloatX( b ) ) );

}