#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint64 ;
typedef  int uint32 ;
struct TYPE_3__ {int* as_uint32; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_reduceCompletely(
    volatile fe25519* inout
)
{
    uint32 numberOfTimesToSubstractPrime;
    uint32 initialGuessForNumberOfTimesToSubstractPrime = inout->as_uint32[7] >>
                                                          31;
    uint64 accu;
    uint8  ctr;

    // add one additional 19 to the estimated number of reductions.
    // Do the calculation without writing back the results to memory.
    //
    // The initial guess of required numbers of reductions is based
    // on bit #32 of the most significant word.
    // This initial guess may be wrong, since we might have a value
    // v in the range
    // 2^255 - 19 <= v < 2^255
    // . After adding 19 to the value, we will be having the correct
    // Number of required subtractions.
    accu = initialGuessForNumberOfTimesToSubstractPrime * 19 + 19;

    for (ctr = 0; ctr < 7; ctr++)
    {
        accu += inout->as_uint32[ctr];
        accu >>= 32;
    }
    accu += inout->as_uint32[7];

    numberOfTimesToSubstractPrime = (uint32)(accu >> 31);

    // Do the reduction.
    accu = numberOfTimesToSubstractPrime * 19;

    for (ctr = 0; ctr < 7; ctr++)
    {
        accu += inout->as_uint32[ctr];
        inout->as_uint32[ctr] = (uint32)accu;
        accu >>= 32;
    }
    accu += inout->as_uint32[7];
    inout->as_uint32[7] = accu & 0x7ffffffful;
}