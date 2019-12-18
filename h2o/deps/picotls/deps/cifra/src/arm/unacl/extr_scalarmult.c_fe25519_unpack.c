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
struct TYPE_3__ {unsigned char* as_uint8; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_unpack(
    volatile fe25519*            out,
    const unsigned char in[32]
)
{
    uint8 ctr;

    for (ctr = 0; ctr < 32; ctr++)
    {
        out->as_uint8[ctr] = in[ctr];
    }
    out->as_uint8[31] &= 0x7f; // make sure that the last bit is cleared.
}