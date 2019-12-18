#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int nConst; TYPE_5__** apExpr; TYPE_2__* pParse; int /*<<< orphan*/  nChng; } ;
typedef  TYPE_3__ WhereConst ;
struct TYPE_12__ {TYPE_3__* pConst; } ;
struct TYPE_15__ {TYPE_1__ u; } ;
typedef  TYPE_4__ Walker ;
struct TYPE_16__ {scalar_t__ op; scalar_t__ iTable; scalar_t__ iColumn; int /*<<< orphan*/  pLeft; } ;
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FixedCol ; 
 int /*<<< orphan*/  EP_Leaf ; 
 int /*<<< orphan*/  ExprClearProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ExprHasProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_COLUMN ; 
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprDup (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int propagateConstantExprRewrite(Walker *pWalker, Expr *pExpr){
  int i;
  WhereConst *pConst;
  if( pExpr->op!=TK_COLUMN ) return WRC_Continue;
  if( ExprHasProperty(pExpr, EP_FixedCol) ) return WRC_Continue;
  pConst = pWalker->u.pConst;
  for(i=0; i<pConst->nConst; i++){
    Expr *pColumn = pConst->apExpr[i*2];
    if( pColumn==pExpr ) continue;
    if( pColumn->iTable!=pExpr->iTable ) continue;
    if( pColumn->iColumn!=pExpr->iColumn ) continue;
    /* A match is found.  Add the EP_FixedCol property */
    pConst->nChng++;
    ExprClearProperty(pExpr, EP_Leaf);
    ExprSetProperty(pExpr, EP_FixedCol);
    assert( pExpr->pLeft==0 );
    pExpr->pLeft = sqlite3ExprDup(pConst->pParse->db, pConst->apExpr[i*2+1], 0);
    break;
  }
  return WRC_Prune;
}