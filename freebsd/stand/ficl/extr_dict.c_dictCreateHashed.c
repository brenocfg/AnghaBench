#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int size; struct TYPE_6__* dict; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_HASH ;
typedef  TYPE_1__ FICL_DICT ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dictEmpty (TYPE_1__*,unsigned int) ; 
 void* ficlMalloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

FICL_DICT  *dictCreateHashed(unsigned nCells, unsigned nHash)
{
    FICL_DICT *pDict;
    size_t nAlloc;

    nAlloc =  sizeof (FICL_HASH) + nCells      * sizeof (CELL)
                                 + (nHash - 1) * sizeof (FICL_WORD *);

    pDict = ficlMalloc(sizeof (FICL_DICT));
    assert(pDict);
    memset(pDict, 0, sizeof (FICL_DICT));
    pDict->dict = ficlMalloc(nAlloc);
    assert(pDict->dict);

    pDict->size = nCells;
    dictEmpty(pDict, nHash);
    return pDict;
}