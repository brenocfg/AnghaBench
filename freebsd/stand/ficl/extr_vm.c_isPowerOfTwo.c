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
typedef  int FICL_UNS ;

/* Variables and functions */

int isPowerOfTwo(FICL_UNS u)
{
    int i = 1;
    FICL_UNS t = 2;

    for (; ((t <= u) && (t != 0)); i++, t <<= 1)
    {
        if (u == t)
            return i;
    }

    return 0;
}