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
struct roundingData {int dummy; } ;
typedef  scalar_t__ sbits64 ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int /*<<< orphan*/  flag ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packFloat64 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  propagateFloat64NaN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat64 (struct roundingData*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 

__attribute__((used)) static float64 addFloat64Sigs( struct roundingData *roundData, float64 a, float64 b, flag zSign )
{
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    expDiff = aExp - bExp;
    aSig <<= 9;
    bSig <<= 9;
    if ( 0 < expDiff ) {
        if ( aExp == 0x7FF ) {
            if ( aSig ) return propagateFloat64NaN( a, b );
            return a;
        }
        if ( bExp == 0 ) {
            --expDiff;
        }
        else {
            bSig |= LIT64( 0x2000000000000000 );
        }
        shift64RightJamming( bSig, expDiff, &bSig );
        zExp = aExp;
    }
    else if ( expDiff < 0 ) {
        if ( bExp == 0x7FF ) {
            if ( bSig ) return propagateFloat64NaN( a, b );
            return packFloat64( zSign, 0x7FF, 0 );
        }
        if ( aExp == 0 ) {
            ++expDiff;
        }
        else {
            aSig |= LIT64( 0x2000000000000000 );
        }
        shift64RightJamming( aSig, - expDiff, &aSig );
        zExp = bExp;
    }
    else {
        if ( aExp == 0x7FF ) {
            if ( aSig | bSig ) return propagateFloat64NaN( a, b );
            return a;
        }
        if ( aExp == 0 ) return packFloat64( zSign, 0, ( aSig + bSig )>>9 );
        zSig = LIT64( 0x4000000000000000 ) + aSig + bSig;
        zExp = aExp;
        goto roundAndPack;
    }
    aSig |= LIT64( 0x2000000000000000 );
    zSig = ( aSig + bSig )<<1;
    --zExp;
    if ( (sbits64) zSig < 0 ) {
        zSig = aSig + bSig;
        ++zExp;
    }
 roundAndPack:
    return roundAndPackFloat64( roundData, zSign, zExp, zSig );

}