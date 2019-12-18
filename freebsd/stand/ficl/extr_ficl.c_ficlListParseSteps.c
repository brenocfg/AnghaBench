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
struct TYPE_9__ {TYPE_1__** parseList; } ;
struct TYPE_8__ {TYPE_3__* pSys; } ;
struct TYPE_7__ {char* name; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  TYPE_3__ FICL_SYSTEM ;

/* Variables and functions */
 int FICL_MAX_PARSE_STEPS ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  vmTextOut (TYPE_2__*,char*,int) ; 

void ficlListParseSteps(FICL_VM *pVM)
{
    int i;
    FICL_SYSTEM *pSys = pVM->pSys;
    assert(pSys);

    vmTextOut(pVM, "Parse steps:", 1);
    vmTextOut(pVM, "lookup", 1);

    for (i = 0; i < FICL_MAX_PARSE_STEPS; i++)
    {
        if (pSys->parseList[i] != NULL)
        {
            vmTextOut(pVM, pSys->parseList[i]->name, 1);
        }
        else break;
    }
    return;
}