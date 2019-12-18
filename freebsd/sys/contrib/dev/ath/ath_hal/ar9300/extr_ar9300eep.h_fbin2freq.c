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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 int AR9300_BCHAN_UNUSED ; 

__attribute__((used)) static inline u_int16_t
fbin2freq(u_int8_t fbin, HAL_BOOL is_2ghz)
{
    /*
    * Reserved value 0xFF provides an empty definition both as
    * an fbin and as a frequency - do not convert
    */
    if (fbin == AR9300_BCHAN_UNUSED)
    {
        return fbin;
    }

    return (u_int16_t)((is_2ghz) ? (2300 + fbin) : (4800 + 5 * fbin));
}