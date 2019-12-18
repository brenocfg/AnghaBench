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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline__ uint32_t GenerateThresh(uint32_t val, int roundup)
{
    uint32_t e = 0;    /* co-efficient, exponent */
    uint32_t oddbit = 0;
    while(val > 0xff) {
        oddbit = val & 1;
        val >>= 1;
        e++;
        if(roundup && oddbit)
            val++;
    }
    return (val | (e << 8));
}