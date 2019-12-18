#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tOptions ;
struct TYPE_4__ {char* argString; } ;
struct TYPE_5__ {scalar_t__ optCookie; TYPE_1__ optArg; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 char* AGALOC (size_t,char*) ; 
 char NUL ; 
 char const* const PLUS_STR ; 
 size_t PLUS_STR_LEN ; 
 int /*<<< orphan*/  memcpy (char*,char const* const,size_t) ; 
 size_t strlen (char const* const) ; 

__attribute__((used)) static void
set_memb_names(tOptions * opts, tOptDesc * od, char const * const * nm_list,
               unsigned int nm_ct)
{
    char *     pz;
    uintptr_t  mask = (1UL << (uintptr_t)nm_ct) - 1UL;
    uintptr_t  bits = (uintptr_t)od->optCookie & mask;
    unsigned int ix = 0;
    size_t     len  = 1;

    /*
     *  Replace the enumeration value with the name string.
     *  First, determine the needed length, then allocate and fill in.
     */
    while (bits != 0) {
        if (bits & 1)
            len += strlen(nm_list[ix]) + PLUS_STR_LEN + 1;
        if (++ix >= nm_ct) break;
        bits >>= 1;
    }

    od->optArg.argString = pz = AGALOC(len, "enum");
    bits = (uintptr_t)od->optCookie & mask;
    if (bits == 0) {
        *pz = NUL;
        return;
    }

    for (ix = 0; ; ix++) {
        size_t nln;
        int    doit = bits & 1;

        bits >>= 1;
        if (doit == 0)
            continue;

        nln = strlen(nm_list[ix]);
        memcpy(pz, nm_list[ix], nln);
        pz += nln;
        if (bits == 0)
            break;
        memcpy(pz, PLUS_STR, PLUS_STR_LEN);
        pz += PLUS_STR_LEN;
    }
    *pz = NUL;
    (void)opts;
}