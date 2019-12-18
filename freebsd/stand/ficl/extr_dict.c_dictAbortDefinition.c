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
struct TYPE_5__ {int /*<<< orphan*/ * here; TYPE_1__* smudge; } ;
struct TYPE_4__ {int flags; scalar_t__ name; } ;
typedef  TYPE_1__ FICL_WORD ;
typedef  TYPE_2__ FICL_DICT ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FW_SMUDGE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ficlLockDictionary (int /*<<< orphan*/ ) ; 

void dictAbortDefinition(FICL_DICT *pDict)
{
    FICL_WORD *pFW;
    ficlLockDictionary(TRUE);
    pFW = pDict->smudge;

    if (pFW->flags & FW_SMUDGE)
        pDict->here = (CELL *)pFW->name;

    ficlLockDictionary(FALSE);
    return;
}