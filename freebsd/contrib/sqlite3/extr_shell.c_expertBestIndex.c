#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct sqlite3_index_constraint {size_t iColumn; int const op; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_19__ {int nConstraint; int nOrderBy; double estimatedCost; TYPE_5__* aOrderBy; TYPE_2__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_6__ sqlite3_index_info ;
struct TYPE_22__ {TYPE_4__* pTab; TYPE_1__* pExpert; } ;
struct TYPE_21__ {size_t iCol; int bRange; struct TYPE_21__* pLink; struct TYPE_21__* pNext; int /*<<< orphan*/  bDesc; } ;
struct TYPE_20__ {TYPE_8__* pOrder; TYPE_8__* pRange; TYPE_8__* pEq; struct TYPE_20__* pNextScan; TYPE_4__* pTab; } ;
struct TYPE_18__ {int iColumn; int /*<<< orphan*/  desc; } ;
struct TYPE_17__ {TYPE_3__* aCol; } ;
struct TYPE_16__ {scalar_t__ iPk; char const* zColl; } ;
struct TYPE_15__ {int argvIndex; } ;
struct TYPE_14__ {TYPE_7__* pScan; } ;
typedef  TYPE_7__ IdxScan ;
typedef  TYPE_8__ IdxConstraint ;
typedef  TYPE_9__ ExpertVtab ;

/* Variables and functions */
 int SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_INDEX_CONSTRAINT_GE ; 
 int SQLITE_INDEX_CONSTRAINT_GT ; 
 int SQLITE_INDEX_CONSTRAINT_LE ; 
 int SQLITE_INDEX_CONSTRAINT_LT ; 
 int SQLITE_OK ; 
 TYPE_7__* idxMalloc (int*,int) ; 
 TYPE_8__* idxNewConstraint (int*,char const*) ; 
 char* sqlite3_vtab_collation (TYPE_6__*,int) ; 

__attribute__((used)) static int expertBestIndex(sqlite3_vtab *pVtab, sqlite3_index_info *pIdxInfo){
  ExpertVtab *p = (ExpertVtab*)pVtab;
  int rc = SQLITE_OK;
  int n = 0;
  IdxScan *pScan;
  const int opmask = 
    SQLITE_INDEX_CONSTRAINT_EQ | SQLITE_INDEX_CONSTRAINT_GT |
    SQLITE_INDEX_CONSTRAINT_LT | SQLITE_INDEX_CONSTRAINT_GE |
    SQLITE_INDEX_CONSTRAINT_LE;

  pScan = idxMalloc(&rc, sizeof(IdxScan));
  if( pScan ){
    int i;

    /* Link the new scan object into the list */
    pScan->pTab = p->pTab;
    pScan->pNextScan = p->pExpert->pScan;
    p->pExpert->pScan = pScan;

    /* Add the constraints to the IdxScan object */
    for(i=0; i<pIdxInfo->nConstraint; i++){
      struct sqlite3_index_constraint *pCons = &pIdxInfo->aConstraint[i];
      if( pCons->usable 
       && pCons->iColumn>=0 
       && p->pTab->aCol[pCons->iColumn].iPk==0
       && (pCons->op & opmask) 
      ){
        IdxConstraint *pNew;
        const char *zColl = sqlite3_vtab_collation(pIdxInfo, i);
        pNew = idxNewConstraint(&rc, zColl);
        if( pNew ){
          pNew->iCol = pCons->iColumn;
          if( pCons->op==SQLITE_INDEX_CONSTRAINT_EQ ){
            pNew->pNext = pScan->pEq;
            pScan->pEq = pNew;
          }else{
            pNew->bRange = 1;
            pNew->pNext = pScan->pRange;
            pScan->pRange = pNew;
          }
        }
        n++;
        pIdxInfo->aConstraintUsage[i].argvIndex = n;
      }
    }

    /* Add the ORDER BY to the IdxScan object */
    for(i=pIdxInfo->nOrderBy-1; i>=0; i--){
      int iCol = pIdxInfo->aOrderBy[i].iColumn;
      if( iCol>=0 ){
        IdxConstraint *pNew = idxNewConstraint(&rc, p->pTab->aCol[iCol].zColl);
        if( pNew ){
          pNew->iCol = iCol;
          pNew->bDesc = pIdxInfo->aOrderBy[i].desc;
          pNew->pNext = pScan->pOrder;
          pNew->pLink = pScan->pOrder;
          pScan->pOrder = pNew;
          n++;
        }
      }
    }
  }

  pIdxInfo->estimatedCost = 1000000.0 / (n+1);
  return rc;
}