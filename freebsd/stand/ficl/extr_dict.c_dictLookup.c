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
typedef  int /*<<< orphan*/  UNS16 ;
struct TYPE_4__ {int /*<<< orphan*/ ** pSearch; scalar_t__ nLists; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_HASH ;
typedef  TYPE_1__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ficlLockDictionary (int) ; 
 int /*<<< orphan*/  hashHashCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FICL_WORD *dictLookup(FICL_DICT *pDict, STRINGINFO si)
{
    FICL_WORD *pFW = NULL;
    FICL_HASH *pHash;
    int i;
    UNS16 hashCode   = hashHashCode(si);

    assert(pDict);

    ficlLockDictionary(1);

    for (i = (int)pDict->nLists - 1; (i >= 0) && (!pFW); --i)
    {
        pHash = pDict->pSearch[i];
        pFW = hashLookup(pHash, si, hashCode);
    }

    ficlLockDictionary(0);
    return pFW;
}