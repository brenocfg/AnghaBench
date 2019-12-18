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
struct TYPE_9__ {int u; } ;
struct TYPE_8__ {scalar_t__ u; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  dict; int /*<<< orphan*/  here; } ;
typedef  TYPE_1__ FICL_DICT ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAlign (TYPE_1__*) ; 
 scalar_t__ dictCellsAvail (TYPE_1__*) ; 
 TYPE_3__ dictIncrease ; 
 TYPE_2__ dictThreshold ; 
 int /*<<< orphan*/  ficlMalloc (int) ; 

void dictCheckThreshold(FICL_DICT* dp)
{
    if( dictCellsAvail(dp) < dictThreshold.u ) {
        dp->dict = ficlMalloc( dictIncrease.u * sizeof (CELL) );
        assert(dp->dict);
        dp->here = dp->dict;
        dp->size = dictIncrease.u;
        dictAlign(dp);
    }
}