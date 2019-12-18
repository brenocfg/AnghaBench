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
struct roundingData {scalar_t__ mode; int /*<<< orphan*/  exception; } ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int flag ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float64_default_nan ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 scalar_t__ float_round_down ; 
 int /*<<< orphan*/  normalizeRoundAndPackFloat64 (struct roundingData*,int,int,int) ; 
 int /*<<< orphan*/  packFloat64 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagateFloat64NaN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 

__attribute__((used)) static float64 subFloat64Sigs( struct roundingData *roundData, float64 a, float64 b, flag zSign )
{
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    expDiff = aExp - bExp;
    aSig <<= 10;
    bSig <<= 10;
    if ( 0 < expDiff ) goto aExpBigger;
    if ( expDiff < 0 ) goto bExpBigger;
    if ( aExp == 0x7FF ) {
        if ( aSig | bSig ) return propagateFloat64NaN( a, b );
        roundData->exception |= float_flag_invalid;
        return float64_default_nan;
    }
    if ( aExp == 0 ) {
        aExp = 1;
        bExp = 1;
    }
    if ( bSig < aSig ) goto aBigger;
    if ( aSig < bSig ) goto bBigger;
    return packFloat64( roundData->mode == float_round_down, 0, 0 );
 bExpBigger:
    if ( bExp == 0x7FF ) {
        if ( bSig ) return propagateFloat64NaN( a, b );
        return packFloat64( zSign ^ 1, 0x7FF, 0 );
    }
    if ( aExp == 0 ) {
        ++expDiff;
    }
    else {
        aSig |= LIT64( 0x4000000000000000 );
    }
    shift64RightJamming( aSig, - expDiff, &aSig );
    bSig |= LIT64( 0x4000000000000000 );
 bBigger:
    zSig = bSig - aSig;
    zExp = bExp;
    zSign ^= 1;
    goto normalizeRoundAndPack;
 aExpBigger:
    if ( aExp == 0x7FF ) {
        if ( aSig ) return propagateFloat64NaN( a, b );
        return a;
    }
    if ( bExp == 0 ) {
        --expDiff;
    }
    else {
        bSig |= LIT64( 0x4000000000000000 );
    }
    shift64RightJamming( bSig, expDiff, &bSig );
    aSig |= LIT64( 0x4000000000000000 );
 aBigger:
    zSig = aSig - bSig;
    zExp = aExp;
 normalizeRoundAndPack:
    --zExp;
    return normalizeRoundAndPackFloat64( roundData, zSign, zExp, zSig );

}