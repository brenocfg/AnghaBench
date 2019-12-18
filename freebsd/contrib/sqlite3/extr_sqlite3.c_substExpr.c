#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  ifNullRow ;
struct TYPE_35__ {int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pPartition; TYPE_7__* pFilter; } ;
typedef  TYPE_5__ Window ;
struct TYPE_38__ {char* zName; } ;
struct TYPE_34__ {TYPE_5__* pWin; } ;
struct TYPE_33__ {int /*<<< orphan*/  pList; int /*<<< orphan*/  pSelect; } ;
struct TYPE_37__ {scalar_t__ iRightJoinTable; scalar_t__ op; scalar_t__ iTable; size_t iColumn; TYPE_4__ y; TYPE_3__ x; struct TYPE_37__* pRight; struct TYPE_37__* pLeft; } ;
struct TYPE_36__ {scalar_t__ iTable; scalar_t__ iNewTable; TYPE_14__* pParse; scalar_t__ isLeftJoin; TYPE_2__* pEList; } ;
struct TYPE_32__ {size_t nExpr; TYPE_1__* a; } ;
struct TYPE_31__ {TYPE_7__* pExpr; } ;
struct TYPE_30__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_6__ SubstContext ;
typedef  TYPE_7__ Expr ;
typedef  TYPE_8__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  EP_CanBeNull ; 
 int /*<<< orphan*/  EP_Collate ; 
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  EP_Subquery ; 
 int /*<<< orphan*/  EP_WinFunc ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 int /*<<< orphan*/  ExprClearProperty (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ExprHasProperty (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_COLLATE ; 
 scalar_t__ TK_COLUMN ; 
 scalar_t__ TK_IF_NULL_ROW ; 
 scalar_t__ TK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* sqlite3ExprAddCollateString (TYPE_14__*,TYPE_7__*,char*) ; 
 TYPE_8__* sqlite3ExprCollSeq (TYPE_14__*,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_7__* sqlite3ExprDup (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3ExprIsVector (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3VectorErrorMsg (TYPE_14__*,TYPE_7__*) ; 
 int /*<<< orphan*/  substExprList (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substSelect (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  testcase (scalar_t__) ; 

__attribute__((used)) static Expr *substExpr(
  SubstContext *pSubst,  /* Description of the substitution */
  Expr *pExpr            /* Expr in which substitution occurs */
){
  if( pExpr==0 ) return 0;
  if( ExprHasProperty(pExpr, EP_FromJoin)
   && pExpr->iRightJoinTable==pSubst->iTable
  ){
    pExpr->iRightJoinTable = pSubst->iNewTable;
  }
  if( pExpr->op==TK_COLUMN && pExpr->iTable==pSubst->iTable ){
    if( pExpr->iColumn<0 ){
      pExpr->op = TK_NULL;
    }else{
      Expr *pNew;
      Expr *pCopy = pSubst->pEList->a[pExpr->iColumn].pExpr;
      Expr ifNullRow;
      assert( pSubst->pEList!=0 && pExpr->iColumn<pSubst->pEList->nExpr );
      assert( pExpr->pRight==0 );
      if( sqlite3ExprIsVector(pCopy) ){
        sqlite3VectorErrorMsg(pSubst->pParse, pCopy);
      }else{
        sqlite3 *db = pSubst->pParse->db;
        if( pSubst->isLeftJoin && pCopy->op!=TK_COLUMN ){
          memset(&ifNullRow, 0, sizeof(ifNullRow));
          ifNullRow.op = TK_IF_NULL_ROW;
          ifNullRow.pLeft = pCopy;
          ifNullRow.iTable = pSubst->iNewTable;
          pCopy = &ifNullRow;
        }
        testcase( ExprHasProperty(pCopy, EP_Subquery) );
        pNew = sqlite3ExprDup(db, pCopy, 0);
        if( pNew && pSubst->isLeftJoin ){
          ExprSetProperty(pNew, EP_CanBeNull);
        }
        if( pNew && ExprHasProperty(pExpr,EP_FromJoin) ){
          pNew->iRightJoinTable = pExpr->iRightJoinTable;
          ExprSetProperty(pNew, EP_FromJoin);
        }
        sqlite3ExprDelete(db, pExpr);
        pExpr = pNew;

        /* Ensure that the expression now has an implicit collation sequence,
        ** just as it did when it was a column of a view or sub-query. */
        if( pExpr ){
          if( pExpr->op!=TK_COLUMN && pExpr->op!=TK_COLLATE ){
            CollSeq *pColl = sqlite3ExprCollSeq(pSubst->pParse, pExpr);
            pExpr = sqlite3ExprAddCollateString(pSubst->pParse, pExpr, 
                (pColl ? pColl->zName : "BINARY")
            );
          }
          ExprClearProperty(pExpr, EP_Collate);
        }
      }
    }
  }else{
    if( pExpr->op==TK_IF_NULL_ROW && pExpr->iTable==pSubst->iTable ){
      pExpr->iTable = pSubst->iNewTable;
    }
    pExpr->pLeft = substExpr(pSubst, pExpr->pLeft);
    pExpr->pRight = substExpr(pSubst, pExpr->pRight);
    if( ExprHasProperty(pExpr, EP_xIsSelect) ){
      substSelect(pSubst, pExpr->x.pSelect, 1);
    }else{
      substExprList(pSubst, pExpr->x.pList);
    }
#ifndef SQLITE_OMIT_WINDOWFUNC
    if( ExprHasProperty(pExpr, EP_WinFunc) ){
      Window *pWin = pExpr->y.pWin;
      pWin->pFilter = substExpr(pSubst, pWin->pFilter);
      substExprList(pSubst, pWin->pPartition);
      substExprList(pSubst, pWin->pOrderBy);
    }
#endif
  }
  return pExpr;
}