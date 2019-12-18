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
typedef  int uint32 ;
typedef  int int8 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int flag ;
typedef  int bits64 ;

/* Variables and functions */
 int countLeadingZeros32 (int) ; 
 int /*<<< orphan*/  packFloat64 (int,int,int) ; 

float64 int32_to_float64( int32 a )
{
    flag aSign;
    uint32 absA;
    int8 shiftCount;
    bits64 zSig;

    if ( a == 0 ) return 0;
    aSign = ( a < 0 );
    absA = aSign ? - a : a;
    shiftCount = countLeadingZeros32( absA ) + 21;
    zSig = absA;
    return packFloat64( aSign, 0x432 - shiftCount, zSig<<shiftCount );

}