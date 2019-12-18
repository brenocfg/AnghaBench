#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i; } ;
struct TYPE_5__ {TYPE_2__ sourceID; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ CELL ;

/* Variables and functions */
 int ficlExecC (TYPE_1__*,char*,int) ; 

int ficlEvaluate(FICL_VM *pVM, char *pText)
{
    int returnValue;
    CELL id = pVM->sourceID;
    pVM->sourceID.i = -1;
    returnValue = ficlExecC(pVM, pText, -1);
    pVM->sourceID = id;
    return returnValue;
}