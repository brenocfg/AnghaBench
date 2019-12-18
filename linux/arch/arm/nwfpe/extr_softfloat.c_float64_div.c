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
struct roundingData {int /*<<< orphan*/  exception; } ;
typedef  scalar_t__ sbits64 ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int flag ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int /*<<< orphan*/  add128 (int,int,int /*<<< orphan*/ ,int,int*,int*) ; 
 int estimateDiv128To64 (int,int /*<<< orphan*/ ,int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 int extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float64_default_nan ; 
 int /*<<< orphan*/  float_flag_divbyzero ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  mul64To128 (int,int,int*,int*) ; 
 int /*<<< orphan*/  normalizeFloat64Subnormal (int,int*,int*) ; 
 int /*<<< orphan*/  packFloat64 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagateFloat64NaN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat64 (struct roundingData*,int,int,int) ; 
 int /*<<< orphan*/  sub128 (int,int /*<<< orphan*/ ,int,int,int*,int*) ; 

float64 float64_div( struct roundingData *roundData, float64 a, float64 b )
{
    flag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    bits64 rem0, rem1;
    bits64 term0, term1;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    bSign = extractFloat64Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0x7FF ) {
        if ( aSig ) return propagateFloat64NaN( a, b );
        if ( bExp == 0x7FF ) {
            if ( bSig ) return propagateFloat64NaN( a, b );
            roundData->exception |= float_flag_invalid;
            return float64_default_nan;
        }
        return packFloat64( zSign, 0x7FF, 0 );
    }
    if ( bExp == 0x7FF ) {
        if ( bSig ) return propagateFloat64NaN( a, b );
        return packFloat64( zSign, 0, 0 );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            if ( ( aExp | aSig ) == 0 ) {
                roundData->exception |= float_flag_invalid;
                return float64_default_nan;
            }
            roundData->exception |= float_flag_divbyzero;
            return packFloat64( zSign, 0x7FF, 0 );
        }
        normalizeFloat64Subnormal( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) return packFloat64( zSign, 0, 0 );
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    }
    zExp = aExp - bExp + 0x3FD;
    aSig = ( aSig | LIT64( 0x0010000000000000 ) )<<10;
    bSig = ( bSig | LIT64( 0x0010000000000000 ) )<<11;
    if ( bSig <= ( aSig + aSig ) ) {
        aSig >>= 1;
        ++zExp;
    }
    zSig = estimateDiv128To64( aSig, 0, bSig );
    if ( ( zSig & 0x1FF ) <= 2 ) {
        mul64To128( bSig, zSig, &term0, &term1 );
        sub128( aSig, 0, term0, term1, &rem0, &rem1 );
        while ( (sbits64) rem0 < 0 ) {
            --zSig;
            add128( rem0, rem1, 0, bSig, &rem0, &rem1 );
        }
        zSig |= ( rem1 != 0 );
    }
    return roundAndPackFloat64( roundData, zSign, zExp, zSig );

}