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
struct TYPE_9__ {int iParentId; struct TYPE_9__* pNext; } ;
struct TYPE_7__ {TYPE_3__* pRow; } ;
struct TYPE_8__ {TYPE_1__ sGraph; } ;
typedef  TYPE_2__ ShellState ;
typedef  TYPE_3__ EQPGraphRow ;

/* Variables and functions */

__attribute__((used)) static EQPGraphRow *eqp_next_row(ShellState *p, int iEqpId, EQPGraphRow *pOld){
  EQPGraphRow *pRow = pOld ? pOld->pNext : p->sGraph.pRow;
  while( pRow && pRow->iParentId!=iEqpId ) pRow = pRow->pNext;
  return pRow;
}