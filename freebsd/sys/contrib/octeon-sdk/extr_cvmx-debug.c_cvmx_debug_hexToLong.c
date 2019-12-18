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
typedef  int uint64_t ;

/* Variables and functions */
 long cvmx_debug_hex (char const) ; 

__attribute__((used)) static int cvmx_debug_hexToLong(const char **ptr, uint64_t *intValue)
{
    int numChars = 0;
    long hexValue;

    *intValue = 0;
    while (**ptr)
    {
        hexValue = cvmx_debug_hex(**ptr);
        if (hexValue < 0)
            break;

        *intValue = (*intValue << 4) | hexValue;
        numChars ++;

        (*ptr)++;
    }

    return(numChars);
}