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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* pCompile; TYPE_1__* smudge; } ;
struct TYPE_8__ {scalar_t__ nName; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ FICL_WORD ;
typedef  TYPE_1__ FICL_HASH ;
typedef  TYPE_3__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FW_SMUDGE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  hashInsertWord (TYPE_1__*,TYPE_1__*) ; 

void dictUnsmudge(FICL_DICT *pDict)
{
    FICL_WORD *pFW = pDict->smudge;
    FICL_HASH *pHash = pDict->pCompile;

    assert(pHash);
    assert(pFW);
    /*
    ** :noname words never get linked into the list...
    */
    if (pFW->nName > 0)
        hashInsertWord(pHash, pFW);
    pFW->flags &= ~(FW_SMUDGE);
    return;
}