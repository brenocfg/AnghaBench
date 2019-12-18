#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* pWInfo; } ;
typedef  TYPE_3__ WhereLoopBuilder ;
struct TYPE_16__ {scalar_t__ op; int iTable; scalar_t__ iColumn; } ;
struct TYPE_15__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_14__ {int nKeyCol; scalar_t__* aiColumn; TYPE_5__* aColExpr; scalar_t__ bUnordered; } ;
struct TYPE_12__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_11__ {TYPE_5__* pOrderBy; } ;
typedef  TYPE_4__ Index ;
typedef  TYPE_5__ ExprList ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 scalar_t__ TK_COLUMN ; 
 scalar_t__ XN_EXPR ; 
 scalar_t__ sqlite3ExprCompareSkip (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* sqlite3ExprSkipCollateAndLikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int indexMightHelpWithOrderBy(
  WhereLoopBuilder *pBuilder,
  Index *pIndex,
  int iCursor
){
  ExprList *pOB;
  ExprList *aColExpr;
  int ii, jj;

  if( pIndex->bUnordered ) return 0;
  if( (pOB = pBuilder->pWInfo->pOrderBy)==0 ) return 0;
  for(ii=0; ii<pOB->nExpr; ii++){
    Expr *pExpr = sqlite3ExprSkipCollateAndLikely(pOB->a[ii].pExpr);
    if( pExpr->op==TK_COLUMN && pExpr->iTable==iCursor ){
      if( pExpr->iColumn<0 ) return 1;
      for(jj=0; jj<pIndex->nKeyCol; jj++){
        if( pExpr->iColumn==pIndex->aiColumn[jj] ) return 1;
      }
    }else if( (aColExpr = pIndex->aColExpr)!=0 ){
      for(jj=0; jj<pIndex->nKeyCol; jj++){
        if( pIndex->aiColumn[jj]!=XN_EXPR ) continue;
        if( sqlite3ExprCompareSkip(pExpr,aColExpr->a[jj].pExpr,iCursor)==0 ){
          return 1;
        }
      }
    }
  }
  return 0;
}