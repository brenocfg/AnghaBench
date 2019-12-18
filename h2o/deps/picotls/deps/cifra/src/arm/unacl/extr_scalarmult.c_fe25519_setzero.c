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
struct TYPE_3__ {scalar_t__* as_uint32; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_setzero(
    fe25519* out
)
{
    uint8 ctr;

    for (ctr = 0; ctr < 8; ctr++)
    {
        out->as_uint32[ctr] = 0;
    }
}