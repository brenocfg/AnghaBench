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
struct TYPE_14__ {int /*<<< orphan*/  zName; } ;
struct TYPE_13__ {scalar_t__ op; scalar_t__ iColumn; int iTable; } ;
struct TYPE_12__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_11__ {char** azColl; scalar_t__* aiColumn; } ;
struct TYPE_10__ {int /*<<< orphan*/  pExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_2__ Index ;
typedef  TYPE_3__ ExprList ;
typedef  TYPE_4__ Expr ;
typedef  TYPE_5__ CollSeq ;

/* Variables and functions */
 scalar_t__ TK_COLUMN ; 
 TYPE_5__* sqlite3ExprNNCollSeq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* sqlite3ExprSkipCollateAndLikely (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int findIndexCol(
  Parse *pParse,                  /* Parse context */
  ExprList *pList,                /* Expression list to search */
  int iBase,                      /* Cursor for table associated with pIdx */
  Index *pIdx,                    /* Index to match column of */
  int iCol                        /* Column of index to match */
){
  int i;
  const char *zColl = pIdx->azColl[iCol];

  for(i=0; i<pList->nExpr; i++){
    Expr *p = sqlite3ExprSkipCollateAndLikely(pList->a[i].pExpr);
    if( p->op==TK_COLUMN
     && p->iColumn==pIdx->aiColumn[iCol]
     && p->iTable==iBase
    ){
      CollSeq *pColl = sqlite3ExprNNCollSeq(pParse, pList->a[i].pExpr);
      if( 0==sqlite3StrICmp(pColl->zName, zColl) ){
        return i;
      }
    }
  }

  return -1;
}