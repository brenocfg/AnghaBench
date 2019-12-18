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
struct TYPE_7__ {TYPE_3__* pSelect; } ;
struct TYPE_8__ {TYPE_1__ u; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_9__ {scalar_t__ pWin; } ;
typedef  TYPE_3__ Select ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resolveRemoveWindowsCb ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void windowRemoveExprFromSelect(Select *pSelect, Expr *pExpr){
  if( pSelect->pWin ){
    Walker sWalker;
    memset(&sWalker, 0, sizeof(Walker));
    sWalker.xExprCallback = resolveRemoveWindowsCb;
    sWalker.u.pSelect = pSelect;
    sqlite3WalkExpr(&sWalker, pExpr);
  }
}