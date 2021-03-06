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
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ FICL_DICT ;

/* Variables and functions */
 int dictCellsUsed (TYPE_1__*) ; 

int dictCellsAvail(FICL_DICT *pDict)
{
    return pDict->size - dictCellsUsed(pDict);
}