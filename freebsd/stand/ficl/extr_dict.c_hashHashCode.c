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
typedef  scalar_t__ UNS8 ;
typedef  int UNS16 ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ cp; } ;
typedef  TYPE_1__ STRINGINFO ;

/* Variables and functions */
 scalar_t__ tolower (scalar_t__) ; 

UNS16 hashHashCode(STRINGINFO si)
{   
    /* hashPJW */
    UNS8 *cp;
    UNS16 code = (UNS16)si.count;
    UNS16 shift = 0;

    if (si.count == 0)
        return 0;

    /* changed to run without errors under Purify -- lch */
    for (cp = (UNS8 *)si.cp; si.count && *cp; cp++, si.count--)
    {
        code = (UNS16)((code << 4) + tolower(*cp));
        shift = (UNS16)(code & 0xf000);
        if (shift)
        {
            code ^= (UNS16)(shift >> 8);
            code ^= (UNS16)shift;
        }
    }

    return (UNS16)code;
}