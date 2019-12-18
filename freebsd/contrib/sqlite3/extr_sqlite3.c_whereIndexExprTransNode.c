#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* pIdxTrans; } ;
struct TYPE_12__ {TYPE_2__ u; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_10__ {scalar_t__ pTab; } ;
struct TYPE_14__ {TYPE_1__ y; int /*<<< orphan*/  iColumn; int /*<<< orphan*/  iTable; int /*<<< orphan*/  op; int /*<<< orphan*/  affExpr; } ;
struct TYPE_13__ {int /*<<< orphan*/  iIdxCol; int /*<<< orphan*/  iIdxCur; int /*<<< orphan*/  iTabCur; int /*<<< orphan*/  pIdxExpr; } ;
typedef  TYPE_4__ IdxExprTrans ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TK_COLUMN ; 
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  sqlite3ExprAffinity (TYPE_5__*) ; 
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int whereIndexExprTransNode(Walker *p, Expr *pExpr){
  IdxExprTrans *pX = p->u.pIdxTrans;
  if( sqlite3ExprCompare(0, pExpr, pX->pIdxExpr, pX->iTabCur)==0 ){
    pExpr->affExpr = sqlite3ExprAffinity(pExpr);
    pExpr->op = TK_COLUMN;
    pExpr->iTable = pX->iIdxCur;
    pExpr->iColumn = pX->iIdxCol;
    pExpr->y.pTab = 0;
    return WRC_Prune;
  }else{
    return WRC_Continue;
  }
}