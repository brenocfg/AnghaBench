#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int uint16 ;
typedef  int int64 ;
typedef  int int32 ;
struct TYPE_5__ {int* as_uint32; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_sub(
    fe25519*       out,
    const fe25519* baseValue,
    const fe25519* valueToSubstract
)
{
    uint16 ctr;
    int64  accu = 0;

    // First subtract the most significant word, so that we may
    // reduce the result "on the fly".
    accu = baseValue->as_uint32[7];
    accu -= valueToSubstract->as_uint32[7];

    // We always set bit #31, and compensate this by subtracting 1 from the reduction
    // value.
    out->as_uint32[7] = ((uint32)accu) | 0x80000000ul;

    accu = 19 * ((int32)(accu >> 31) - 1);
    // ^ "-1" is the compensation for the "| 0x80000000ul" above.
    // This choice makes sure, that the result will be positive!

    for (ctr = 0; ctr < 7; ctr += 1)
    {
        accu += baseValue->as_uint32[ctr];
        accu -= valueToSubstract->as_uint32[ctr];

        out->as_uint32[ctr] = (uint32)accu;
        accu >>= 32;
    }
    accu += out->as_uint32[7];
    out->as_uint32[7] = (uint32)accu;
}