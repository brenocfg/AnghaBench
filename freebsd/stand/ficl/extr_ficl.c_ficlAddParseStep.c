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
struct TYPE_3__ {int /*<<< orphan*/ ** parseList; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_SYSTEM ;

/* Variables and functions */
 int FICL_MAX_PARSE_STEPS ; 

int ficlAddParseStep(FICL_SYSTEM *pSys, FICL_WORD *pFW)
{
    int i;
    for (i = 0; i < FICL_MAX_PARSE_STEPS; i++)
    {
        if (pSys->parseList[i] == NULL)
        {
            pSys->parseList[i] = pFW;
            return 0;
        }
    }

    return 1;
}