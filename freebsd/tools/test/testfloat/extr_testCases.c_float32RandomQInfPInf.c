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
typedef  int float32 ;

/* Variables and functions */
 int float32NumQInfWeightMasks ; 
 int* float32QInfWeightMasks ; 
 int* float32QInfWeightOffsets ; 
 int randomUint16 () ; 
 int randomUint32 () ; 
 int randomUint8 () ; 

__attribute__((used)) static float32 float32RandomQInfPInf( void )
{
    int8 weightMaskNum;

    weightMaskNum = randomUint8() % float32NumQInfWeightMasks;
    return
          ( ( (uint32) ( randomUint8() & 1 ) )<<31 )
        | (   (   ( ( (uint32) ( randomUint16() & 0x1FF ) )<<23 )
                & float32QInfWeightMasks[ weightMaskNum ] )
            + float32QInfWeightOffsets[ weightMaskNum ]
          )
        | ( randomUint32() & 0x007FFFFF );

}