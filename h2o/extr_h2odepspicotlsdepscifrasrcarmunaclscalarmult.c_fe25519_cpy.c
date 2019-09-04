#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_4__ {int /*<<< orphan*/ * as_uint32; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_cpy(
    fe25519*       dest,
    const fe25519* source
)
{
    uint32 ctr;

    for (ctr = 0; ctr < 8; ctr++)
    {
        dest->as_uint32[ctr] = source->as_uint32[ctr];
    }
}