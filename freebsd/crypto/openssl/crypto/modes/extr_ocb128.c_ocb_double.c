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
struct TYPE_4__ {int* c; } ;
typedef  TYPE_1__ OCB_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ocb_block_lshift (int*,int,int*) ; 

__attribute__((used)) static void ocb_double(OCB_BLOCK *in, OCB_BLOCK *out)
{
    unsigned char mask;

    /*
     * Calculate the mask based on the most significant bit. There are more
     * efficient ways to do this - but this way is constant time
     */
    mask = in->c[0] & 0x80;
    mask >>= 7;
    mask = (0 - mask) & 0x87;

    ocb_block_lshift(in->c, 1, out->c);

    out->c[15] ^= mask;
}