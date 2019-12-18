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
typedef  int sbits32 ;
typedef  size_t int8 ;
typedef  int int16 ;
typedef  int bits64 ;
typedef  int bits32 ;
typedef  int bits16 ;

/* Variables and functions */

__attribute__((used)) static bits32 estimateSqrt32( int16 aExp, bits32 a )
{
    static const bits16 sqrtOddAdjustments[] = {
        0x0004, 0x0022, 0x005D, 0x00B1, 0x011D, 0x019F, 0x0236, 0x02E0,
        0x039C, 0x0468, 0x0545, 0x0631, 0x072B, 0x0832, 0x0946, 0x0A67
    };
    static const bits16 sqrtEvenAdjustments[] = {
        0x0A2D, 0x08AF, 0x075A, 0x0629, 0x051A, 0x0429, 0x0356, 0x029E,
        0x0200, 0x0179, 0x0109, 0x00AF, 0x0068, 0x0034, 0x0012, 0x0002
    };
    int8 idx;
    bits32 z;

    idx = ( a>>27 ) & 15;
    if ( aExp & 1 ) {
        z = 0x4000 + ( a>>17 ) - sqrtOddAdjustments[ idx ];
        z = ( ( a / z )<<14 ) + ( z<<15 );
        a >>= 1;
    }
    else {
        z = 0x8000 + ( a>>17 ) - sqrtEvenAdjustments[ idx ];
        z = a / z + z;
        z = ( 0x20000 <= z ) ? 0xFFFF8000 : ( z<<15 );
        if ( z <= a ) return (bits32) ( ( (sbits32) a )>>1 );
    }
    return ( (bits32) ( ( ( (bits64) a )<<31 ) / z ) ) + ( z>>1 );

}