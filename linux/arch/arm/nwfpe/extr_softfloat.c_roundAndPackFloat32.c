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
struct roundingData {scalar_t__ mode; int exception; } ;
typedef  scalar_t__ sbits32 ;
typedef  scalar_t__ int8 ;
typedef  int int16 ;
typedef  scalar_t__ float32 ;
typedef  int flag ;
typedef  int bits32 ;
typedef  int bits16 ;

/* Variables and functions */
 scalar_t__ float_detect_tininess ; 
 int float_flag_inexact ; 
 int float_flag_overflow ; 
 int float_flag_underflow ; 
 scalar_t__ float_round_down ; 
 scalar_t__ float_round_nearest_even ; 
 scalar_t__ float_round_to_zero ; 
 scalar_t__ float_round_up ; 
 scalar_t__ float_tininess_before_rounding ; 
 scalar_t__ packFloat32 (int,int,int) ; 
 int /*<<< orphan*/  shift32RightJamming (int,int,int*) ; 

__attribute__((used)) static float32 roundAndPackFloat32( struct roundingData *roundData, flag zSign, int16 zExp, bits32 zSig )
{
    int8 roundingMode;
    flag roundNearestEven;
    int8 roundIncrement, roundBits;
    flag isTiny;

    roundingMode = roundData->mode;
    roundNearestEven = ( roundingMode == float_round_nearest_even );
    roundIncrement = 0x40;
    if ( ! roundNearestEven ) {
        if ( roundingMode == float_round_to_zero ) {
            roundIncrement = 0;
        }
        else {
            roundIncrement = 0x7F;
            if ( zSign ) {
                if ( roundingMode == float_round_up ) roundIncrement = 0;
            }
            else {
                if ( roundingMode == float_round_down ) roundIncrement = 0;
            }
        }
    }
    roundBits = zSig & 0x7F;
    if ( 0xFD <= (bits16) zExp ) {
        if (    ( 0xFD < zExp )
             || (    ( zExp == 0xFD )
                  && ( (sbits32) ( zSig + roundIncrement ) < 0 ) )
           ) {
            roundData->exception |= float_flag_overflow | float_flag_inexact;
            return packFloat32( zSign, 0xFF, 0 ) - ( roundIncrement == 0 );
        }
        if ( zExp < 0 ) {
            isTiny =
                   ( float_detect_tininess == float_tininess_before_rounding )
                || ( zExp < -1 )
                || ( zSig + roundIncrement < 0x80000000 );
            shift32RightJamming( zSig, - zExp, &zSig );
            zExp = 0;
            roundBits = zSig & 0x7F;
            if ( isTiny && roundBits ) roundData->exception |= float_flag_underflow;
        }
    }
    if ( roundBits ) roundData->exception |= float_flag_inexact;
    zSig = ( zSig + roundIncrement )>>7;
    zSig &= ~ ( ( ( roundBits ^ 0x40 ) == 0 ) & roundNearestEven );
    if ( zSig == 0 ) zExp = 0;
    return packFloat32( zSign, zExp, zSig );

}