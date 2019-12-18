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
typedef  int int32 ;
typedef  int int16 ;
typedef  int float32 ;
typedef  scalar_t__ flag ;
typedef  int bits32 ;

/* Variables and functions */
 int extractFloat32Exp (int) ; 
 int extractFloat32Frac (int) ; 
 scalar_t__ extractFloat32Sign (int) ; 
 int /*<<< orphan*/  float_flag_inexact ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 

int32 float32_to_int32_round_to_zero( float32 a )
{
    flag aSign;
    int16 aExp, shiftCount;
    bits32 aSig;
    int32 z;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    shiftCount = aExp - 0x9E;
    if ( 0 <= shiftCount ) {
        if ( a == 0xCF000000 ) return 0x80000000;
        float_raise( float_flag_invalid );
        if ( ! aSign || ( ( aExp == 0xFF ) && aSig ) ) return 0x7FFFFFFF;
        return 0x80000000;
    }
    else if ( aExp <= 0x7E ) {
        if ( aExp | aSig ) float_raise( float_flag_inexact );
        return 0;
    }
    aSig = ( aSig | 0x00800000 )<<8;
    z = aSig>>( - shiftCount );
    if ( (bits32) ( aSig<<( shiftCount & 31 ) ) ) {
        float_raise( float_flag_inexact );
    }
    return aSign ? - z : z;

}