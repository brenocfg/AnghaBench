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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_5__ {int* as_uint32; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_add(
    fe25519*       out,
    const fe25519* baseValue,
    const fe25519* valueToAdd
)
{
    uint16 ctr = 0;
    uint64 accu = 0;

    // We first add the most significant word, so that we may reduce
    // "on the fly".
    accu = baseValue->as_uint32[7];
    accu += valueToAdd->as_uint32[7];
    out->as_uint32[7] = ((uint32)accu) & 0x7ffffffful;

    accu = ((uint32)(accu >> 31)) * 19;

    for (ctr = 0; ctr < 7; ctr += 1)
    {
        accu += baseValue->as_uint32[ctr];
        accu += valueToAdd->as_uint32[ctr];

        out->as_uint32[ctr] = (uint32)accu;
        accu >>= 32;
    }
    accu += out->as_uint32[7];
    out->as_uint32[7] = (uint32)accu;
}