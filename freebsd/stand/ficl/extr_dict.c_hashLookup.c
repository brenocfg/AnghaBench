#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UNS16 ;
struct TYPE_9__ {int size; TYPE_2__** table; struct TYPE_9__* link; } ;
struct TYPE_8__ {scalar_t__ nName; struct TYPE_8__* link; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ count; int /*<<< orphan*/  cp; } ;
typedef  TYPE_1__ STRINGINFO ;
typedef  TYPE_2__ FICL_WORD ;
typedef  scalar_t__ FICL_UNS ;
typedef  TYPE_3__ FICL_HASH ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nFICLNAME ; 
 int /*<<< orphan*/  strincmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

FICL_WORD *hashLookup(FICL_HASH *pHash, STRINGINFO si, UNS16 hashCode)
{
    FICL_UNS nCmp = si.count;
    FICL_WORD *pFW;
    UNS16 hashIdx;

    if (nCmp > nFICLNAME)
        nCmp = nFICLNAME;

    for (; pHash != NULL; pHash = pHash->link)
    {
        if (pHash->size > 1)
            hashIdx = (UNS16)(hashCode % pHash->size);
        else            /* avoid the modulo op for single threaded lists */
            hashIdx = 0;

        for (pFW = pHash->table[hashIdx]; pFW; pFW = pFW->link)
        {
            if ( (pFW->nName == si.count) 
                && (!strincmp(si.cp, pFW->name, nCmp)) )
                return pFW;
#if FICL_ROBUST
            assert(pFW != pFW->link);
#endif
        }
    }

    return NULL;
}