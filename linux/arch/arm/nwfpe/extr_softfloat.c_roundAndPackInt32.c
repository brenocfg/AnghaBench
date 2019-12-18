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
typedef  scalar_t__ int8 ;
typedef  int int32 ;
typedef  int flag ;
typedef  int bits64 ;

/* Variables and functions */
 int /*<<< orphan*/  float_flag_inexact ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 scalar_t__ float_round_down ; 
 scalar_t__ float_round_nearest_even ; 
 scalar_t__ float_round_to_zero ; 
 scalar_t__ float_round_up ; 

__attribute__((used)) static int32 roundAndPackInt32( struct roundingData *roundData, flag zSign, bits64 absZ )
{
    int8 roundingMode;
    flag roundNearestEven;
    int8 roundIncrement, roundBits;
    int32 z;

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
    roundBits = absZ & 0x7F;
    absZ = ( absZ + roundIncrement )>>7;
    absZ &= ~ ( ( ( roundBits ^ 0x40 ) == 0 ) & roundNearestEven );
    z = absZ;
    if ( zSign ) z = - z;
    if ( ( absZ>>32 ) || ( z && ( ( z < 0 ) ^ zSign ) ) ) {
        roundData->exception |= float_flag_invalid;
        return zSign ? 0x80000000 : 0x7FFFFFFF;
    }
    if ( roundBits ) roundData->exception |= float_flag_inexact;
    return z;

}