#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* pRow; } ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
struct TYPE_6__ {TYPE_4__ sGraph; } ;
typedef  TYPE_1__ ShellState ;
typedef  TYPE_2__ EQPGraphRow ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void eqp_reset(ShellState *p){
  EQPGraphRow *pRow, *pNext;
  for(pRow = p->sGraph.pRow; pRow; pRow = pNext){
    pNext = pRow->pNext;
    sqlite3_free(pRow);
  }
  memset(&p->sGraph, 0, sizeof(p->sGraph));
}