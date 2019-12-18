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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */

__attribute__((used)) static int num_bits_ulong(unsigned long value)
{
    size_t i;
    unsigned long ret = 0;

    /*
     * It is argued that *on average* constant counter loop performs
     * not worse [if not better] than one with conditional break or
     * mask-n-table-lookup-style, because of branch misprediction
     * penalties.
     */
    for (i = 0; i < sizeof(value) * 8; i++) {
        ret += (value != 0);
        value >>= 1;
    }

    return (int)ret;
}