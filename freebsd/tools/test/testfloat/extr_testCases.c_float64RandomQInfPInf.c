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
typedef  size_t int8 ;
typedef  int /*<<< orphan*/  float64 ;

/* Variables and functions */
 int /*<<< orphan*/  SETFLOAT64 (int /*<<< orphan*/ ,int,int) ; 
 int float64NumQInfWeightMasks ; 
 int* float64QInfWeightMasks ; 
 int* float64QInfWeightOffsets ; 
 int randomUint16 () ; 
 int randomUint32 () ; 
 int randomUint8 () ; 

__attribute__((used)) static float64 float64RandomQInfPInf( void )
{
    int8 weightMaskNum;
    float64 z;

    weightMaskNum = randomUint8() % float64NumQInfWeightMasks;
    SETFLOAT64(
        z,
          ( ( (uint32) ( randomUint8() & 1 ) )<<31 )
        | (   (   ( ( (uint32) ( randomUint16() & 0xFFF ) )<<20 )
                & float64QInfWeightMasks[ weightMaskNum ] )
            + float64QInfWeightOffsets[ weightMaskNum ]
          )
        | ( randomUint32() & 0x000FFFFF ),
        randomUint32()
    );
    return z;

}