#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ iOrderByCol; } ;
struct TYPE_26__ {TYPE_1__ x; } ;
struct ExprList_item {int /*<<< orphan*/  sortFlags; TYPE_8__* pExpr; TYPE_2__ u; } ;
struct TYPE_27__ {TYPE_9__* pDfltColl; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_33__ {int /*<<< orphan*/  zName; } ;
struct TYPE_32__ {int flags; } ;
struct TYPE_31__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_30__ {int /*<<< orphan*/ * aSortFlags; TYPE_9__** aColl; } ;
struct TYPE_29__ {TYPE_3__* db; } ;
struct TYPE_28__ {TYPE_7__* pOrderBy; } ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ Parse ;
typedef  TYPE_6__ KeyInfo ;
typedef  TYPE_7__ ExprList ;
typedef  TYPE_8__ Expr ;
typedef  TYPE_9__ CollSeq ;

/* Variables and functions */
 int EP_Collate ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_9__* multiSelectCollSeq (TYPE_5__*,TYPE_4__*,scalar_t__) ; 
 TYPE_8__* sqlite3ExprAddCollateString (TYPE_5__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* sqlite3ExprCollSeq (TYPE_5__*,TYPE_8__*) ; 
 TYPE_6__* sqlite3KeyInfoAlloc (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  sqlite3KeyInfoIsWriteable (TYPE_6__*) ; 

__attribute__((used)) static KeyInfo *multiSelectOrderByKeyInfo(Parse *pParse, Select *p, int nExtra){
  ExprList *pOrderBy = p->pOrderBy;
  int nOrderBy = p->pOrderBy->nExpr;
  sqlite3 *db = pParse->db;
  KeyInfo *pRet = sqlite3KeyInfoAlloc(db, nOrderBy+nExtra, 1);
  if( pRet ){
    int i;
    for(i=0; i<nOrderBy; i++){
      struct ExprList_item *pItem = &pOrderBy->a[i];
      Expr *pTerm = pItem->pExpr;
      CollSeq *pColl;

      if( pTerm->flags & EP_Collate ){
        pColl = sqlite3ExprCollSeq(pParse, pTerm);
      }else{
        pColl = multiSelectCollSeq(pParse, p, pItem->u.x.iOrderByCol-1);
        if( pColl==0 ) pColl = db->pDfltColl;
        pOrderBy->a[i].pExpr =
          sqlite3ExprAddCollateString(pParse, pTerm, pColl->zName);
      }
      assert( sqlite3KeyInfoIsWriteable(pRet) );
      pRet->aColl[i] = pColl;
      pRet->aSortFlags[i] = pOrderBy->a[i].sortFlags;
    }
  }

  return pRet;
}