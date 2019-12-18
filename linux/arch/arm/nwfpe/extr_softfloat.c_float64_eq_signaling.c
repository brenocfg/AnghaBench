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
typedef  int float64 ;
typedef  int flag ;
typedef  scalar_t__ bits64 ;

/* Variables and functions */
 int extractFloat64Exp (int) ; 
 scalar_t__ extractFloat64Frac (int) ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 

flag float64_eq_signaling( float64 a, float64 b )
{

    if (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) {
        float_raise( float_flag_invalid );
        return 0;
    }
    return ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );

}