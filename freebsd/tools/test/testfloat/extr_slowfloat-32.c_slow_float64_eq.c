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
typedef  int /*<<< orphan*/  flag ;

/* Variables and functions */
 int /*<<< orphan*/  float64ToFloatX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floatXEq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

flag slow_float64_eq( float64 a, float64 b )
{

    return floatXEq( float64ToFloatX( a ), float64ToFloatX( b ) );

}