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
typedef  scalar_t__ sbits64 ;
typedef  scalar_t__ int8 ;
typedef  int int16 ;
typedef  scalar_t__ float64 ;
typedef  int flag ;
typedef  int bits64 ;
typedef  int bits16 ;

/* Variables and functions */
 int LIT64 (int) ; 
 scalar_t__ float_detect_tininess ; 
 int float_flag_inexact ; 
 int float_flag_overflow ; 
 int float_flag_underflow ; 
 scalar_t__ float_round_down ; 
 scalar_t__ float_round_nearest_even ; 
 scalar_t__ float_round_to_zero ; 
 scalar_t__ float_round_up ; 
 scalar_t__ float_tininess_before_rounding ; 
 scalar_t__ packFloat64 (int,int,int) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 

__attribute__((used)) static float64 roundAndPackFloat64( struct roundingData *roundData, flag zSign, int16 zExp, bits64 zSig )
{
    int8 roundingMode;
    flag roundNearestEven;
    int16 roundIncrement, roundBits;
    flag isTiny;

    roundingMode = roundData->mode;
    roundNearestEven = ( roundingMode == float_round_nearest_even );
    roundIncrement = 0x200;
    if ( ! roundNearestEven ) {
        if ( roundingMode == float_round_to_zero ) {
            roundIncrement = 0;
        }
        else {
            roundIncrement = 0x3FF;
            if ( zSign ) {
                if ( roundingMode == float_round_up ) roundIncrement = 0;
            }
            else {
                if ( roundingMode == float_round_down ) roundIncrement = 0;
            }
        }
    }
    roundBits = zSig & 0x3FF;
    if ( 0x7FD <= (bits16) zExp ) {
        if (    ( 0x7FD < zExp )
             || (    ( zExp == 0x7FD )
                  && ( (sbits64) ( zSig + roundIncrement ) < 0 ) )
           ) {
            //register int lr = __builtin_return_address(0);
            //printk("roundAndPackFloat64 called from 0x%08x\n",lr);
            roundData->exception |= float_flag_overflow | float_flag_inexact;
            return packFloat64( zSign, 0x7FF, 0 ) - ( roundIncrement == 0 );
        }
        if ( zExp < 0 ) {
            isTiny =
                   ( float_detect_tininess == float_tininess_before_rounding )
                || ( zExp < -1 )
                || ( zSig + roundIncrement < LIT64( 0x8000000000000000 ) );
            shift64RightJamming( zSig, - zExp, &zSig );
            zExp = 0;
            roundBits = zSig & 0x3FF;
            if ( isTiny && roundBits ) roundData->exception |= float_flag_underflow;
        }
    }
    if ( roundBits ) roundData->exception |= float_flag_inexact;
    zSig = ( zSig + roundIncrement )>>10;
    zSig &= ~ ( ( ( roundBits ^ 0x200 ) == 0 ) & roundNearestEven );
    if ( zSig == 0 ) zExp = 0;
    return packFloat64( zSign, zExp, zSig );

}