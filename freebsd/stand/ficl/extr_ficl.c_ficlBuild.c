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
struct TYPE_3__ {int /*<<< orphan*/  dp; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_CODE ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dictAppendWord (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char) ; 
 int dictCellsAvail (int /*<<< orphan*/ ) ; 
 int ficlLockDictionary (int /*<<< orphan*/ ) ; 

int ficlBuild(FICL_SYSTEM *pSys, char *name, FICL_CODE code, char flags)
{
#if FICL_MULTITHREAD
    int err = ficlLockDictionary(TRUE);
    if (err) return err;
#endif /* FICL_MULTITHREAD */

    assert(dictCellsAvail(pSys->dp) > sizeof (FICL_WORD) / sizeof (CELL));
    dictAppendWord(pSys->dp, name, code, flags);

    ficlLockDictionary(FALSE);
    return 0;
}