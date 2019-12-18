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
 int /*<<< orphan*/  float32ToFloatX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floatXRoundToInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floatXToFloat32 (int /*<<< orphan*/ ) ; 

float32 slow_float32_round_to_int( float32 a )
{

    return floatXToFloat32( floatXRoundToInt( float32ToFloatX( a ) ) );

}