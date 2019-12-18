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

/* Variables and functions */

__attribute__((used)) static void ocb_block_xor(const unsigned char *in1,
                          const unsigned char *in2, size_t len,
                          unsigned char *out)
{
    size_t i;
    for (i = 0; i < len; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}