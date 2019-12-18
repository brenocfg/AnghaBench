#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Walker ;
struct TYPE_5__ {int /*<<< orphan*/  pUpsertTargetWhere; int /*<<< orphan*/  pUpsertWhere; int /*<<< orphan*/  pUpsertSet; int /*<<< orphan*/  pUpsertTarget; } ;
typedef  TYPE_1__ Upsert ;
struct TYPE_6__ {TYPE_1__* pUpsert; int /*<<< orphan*/  pExprList; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pSelect; struct TYPE_6__* pNext; } ;
typedef  TYPE_2__ TriggerStep ;
struct TYPE_7__ {TYPE_2__* step_list; int /*<<< orphan*/  pWhen; } ;
typedef  TYPE_3__ Trigger ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3WalkExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WalkExprList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WalkSelect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renameWalkTrigger(Walker *pWalker, Trigger *pTrigger){
  TriggerStep *pStep;

  /* Find tokens to edit in WHEN clause */
  sqlite3WalkExpr(pWalker, pTrigger->pWhen);

  /* Find tokens to edit in trigger steps */
  for(pStep=pTrigger->step_list; pStep; pStep=pStep->pNext){
    sqlite3WalkSelect(pWalker, pStep->pSelect);
    sqlite3WalkExpr(pWalker, pStep->pWhere);
    sqlite3WalkExprList(pWalker, pStep->pExprList);
    if( pStep->pUpsert ){
      Upsert *pUpsert = pStep->pUpsert;
      sqlite3WalkExprList(pWalker, pUpsert->pUpsertTarget);
      sqlite3WalkExprList(pWalker, pUpsert->pUpsertSet);
      sqlite3WalkExpr(pWalker, pUpsert->pUpsertWhere);
      sqlite3WalkExpr(pWalker, pUpsert->pUpsertTargetWhere);
    }
  }
}