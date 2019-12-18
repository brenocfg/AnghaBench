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
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int /*<<< orphan*/  float32 ;
typedef  int /*<<< orphan*/  flag ;
typedef  int bits64 ;
typedef  int bits32 ;

/* Variables and functions */
 scalar_t__ extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat32 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 

float32 float64_to_float32(float64 a)
{
    flag aSign;
    int16 aExp;
    bits64 aSig;
    bits32 zSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );

    shift64RightJamming( aSig, 22, &aSig );
    zSig = aSig;
    if ( aExp || zSig ) {
        zSig |= 0x40000000;
        aExp -= 0x381;
    }
    return roundAndPackFloat32(aSign, aExp, zSig);
}