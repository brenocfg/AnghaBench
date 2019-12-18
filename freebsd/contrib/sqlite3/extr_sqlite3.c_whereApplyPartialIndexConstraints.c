#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int wtFlags; TYPE_3__* pExpr; } ;
typedef  TYPE_1__ WhereTerm ;
struct TYPE_9__ {int nTerm; TYPE_1__* a; } ;
typedef  TYPE_2__ WhereClause ;
struct TYPE_10__ {scalar_t__ op; struct TYPE_10__* pRight; struct TYPE_10__* pLeft; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int TERM_CODED ; 
 scalar_t__ TK_AND ; 
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static void whereApplyPartialIndexConstraints(
  Expr *pTruth,
  int iTabCur,
  WhereClause *pWC
){
  int i;
  WhereTerm *pTerm;
  while( pTruth->op==TK_AND ){
    whereApplyPartialIndexConstraints(pTruth->pLeft, iTabCur, pWC);
    pTruth = pTruth->pRight;
  }
  for(i=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
    Expr *pExpr;
    if( pTerm->wtFlags & TERM_CODED ) continue;
    pExpr = pTerm->pExpr;
    if( sqlite3ExprCompare(0, pExpr, pTruth, iTabCur)==0 ){
      pTerm->wtFlags |= TERM_CODED;
    }
  }
}