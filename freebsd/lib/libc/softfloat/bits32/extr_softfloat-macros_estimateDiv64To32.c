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
typedef  scalar_t__ sbits32 ;
typedef  int bits32 ;

/* Variables and functions */
 int /*<<< orphan*/  add64 (int,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  mul32To64 (int,int,int*,int*) ; 
 int /*<<< orphan*/  sub64 (int,int,int,int,int*,int*) ; 

__attribute__((used)) static bits32 estimateDiv64To32( bits32 a0, bits32 a1, bits32 b )
{
    bits32 b0, b1;
    bits32 rem0, rem1, term0, term1;
    bits32 z;

    if ( b <= a0 ) return 0xFFFFFFFF;
    b0 = b>>16;
    z = ( b0<<16 <= a0 ) ? 0xFFFF0000 : ( a0 / b0 )<<16;
    mul32To64( b, z, &term0, &term1 );
    sub64( a0, a1, term0, term1, &rem0, &rem1 );
    while ( ( (sbits32) rem0 ) < 0 ) {
        z -= 0x10000;
        b1 = b<<16;
        add64( rem0, rem1, b0, b1, &rem0, &rem1 );
    }
    rem0 = ( rem0<<16 ) | ( rem1>>16 );
    z |= ( b0<<16 <= rem0 ) ? 0xFFFF : rem0 / b0;
    return z;

}