#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sqlite3_index_orderby {int desc; int /*<<< orphan*/  iColumn; } ;
struct sqlite3_index_constraint_usage {int dummy; } ;
struct sqlite3_index_constraint {int iColumn; int iTermOffset; int op; } ;
struct TYPE_18__ {int jointype; } ;
struct SrcList_item {scalar_t__ iCursor; TYPE_1__ fg; } ;
struct HiddenIndexInfo {TYPE_7__* pParse; TYPE_6__* pWC; } ;
struct TYPE_21__ {int /*<<< orphan*/  aConstraintUsage; int /*<<< orphan*/  aOrderBy; int /*<<< orphan*/  aConstraint; int /*<<< orphan*/  nOrderBy; int /*<<< orphan*/  nConstraint; } ;
typedef  TYPE_4__ sqlite3_index_info ;
struct TYPE_19__ {int leftColumn; } ;
struct TYPE_22__ {scalar_t__ leftCursor; int prereqRight; int eOperator; int wtFlags; int eMatchOp; TYPE_16__* pExpr; TYPE_2__ u; } ;
typedef  TYPE_5__ WhereTerm ;
struct TYPE_23__ {int nTerm; TYPE_5__* a; } ;
typedef  TYPE_6__ WhereClause ;
struct TYPE_26__ {scalar_t__ op; scalar_t__ iTable; int /*<<< orphan*/  iColumn; } ;
struct TYPE_25__ {int nExpr; TYPE_3__* a; } ;
struct TYPE_24__ {int /*<<< orphan*/  db; } ;
struct TYPE_20__ {int sortFlags; TYPE_9__* pExpr; } ;
struct TYPE_17__ {int /*<<< orphan*/  pRight; } ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ ExprList ;
typedef  TYPE_9__ Expr ;
typedef  int Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_16__*,int /*<<< orphan*/ ) ; 
 int IsPowerOfTwo (int) ; 
 int JT_LEFT ; 
 int KEYINFO_ORDER_BIGNULL ; 
 int KEYINFO_ORDER_DESC ; 
 int SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_INDEX_CONSTRAINT_GE ; 
 int SQLITE_INDEX_CONSTRAINT_GT ; 
 int SQLITE_INDEX_CONSTRAINT_IS ; 
 int SQLITE_INDEX_CONSTRAINT_ISNULL ; 
 int SQLITE_INDEX_CONSTRAINT_LE ; 
 int SQLITE_INDEX_CONSTRAINT_LT ; 
 int TERM_VNULL ; 
 scalar_t__ TK_COLUMN ; 
 int WO_ALL ; 
 int WO_AUX ; 
 int WO_EQ ; 
 int WO_EQUIV ; 
 int WO_GE ; 
 int WO_GT ; 
 int WO_IN ; 
 int WO_IS ; 
 int WO_ISNULL ; 
 int WO_LE ; 
 int WO_LT ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* sqlite3DbMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_7__*,char*) ; 
 scalar_t__ sqlite3ExprIsVector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static sqlite3_index_info *allocateIndexInfo(
  Parse *pParse,                  /* The parsing context */
  WhereClause *pWC,               /* The WHERE clause being analyzed */
  Bitmask mUnusable,              /* Ignore terms with these prereqs */
  struct SrcList_item *pSrc,      /* The FROM clause term that is the vtab */
  ExprList *pOrderBy,             /* The ORDER BY clause */
  u16 *pmNoOmit                   /* Mask of terms not to omit */
){
  int i, j;
  int nTerm;
  struct sqlite3_index_constraint *pIdxCons;
  struct sqlite3_index_orderby *pIdxOrderBy;
  struct sqlite3_index_constraint_usage *pUsage;
  struct HiddenIndexInfo *pHidden;
  WhereTerm *pTerm;
  int nOrderBy;
  sqlite3_index_info *pIdxInfo;
  u16 mNoOmit = 0;

  /* Count the number of possible WHERE clause constraints referring
  ** to this virtual table */
  for(i=nTerm=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
    if( pTerm->leftCursor != pSrc->iCursor ) continue;
    if( pTerm->prereqRight & mUnusable ) continue;
    assert( IsPowerOfTwo(pTerm->eOperator & ~WO_EQUIV) );
    testcase( pTerm->eOperator & WO_IN );
    testcase( pTerm->eOperator & WO_ISNULL );
    testcase( pTerm->eOperator & WO_IS );
    testcase( pTerm->eOperator & WO_ALL );
    if( (pTerm->eOperator & ~(WO_EQUIV))==0 ) continue;
    if( pTerm->wtFlags & TERM_VNULL ) continue;
    assert( pTerm->u.leftColumn>=(-1) );
    nTerm++;
  }

  /* If the ORDER BY clause contains only columns in the current 
  ** virtual table then allocate space for the aOrderBy part of
  ** the sqlite3_index_info structure.
  */
  nOrderBy = 0;
  if( pOrderBy ){
    int n = pOrderBy->nExpr;
    for(i=0; i<n; i++){
      Expr *pExpr = pOrderBy->a[i].pExpr;
      if( pExpr->op!=TK_COLUMN || pExpr->iTable!=pSrc->iCursor ) break;
      if( pOrderBy->a[i].sortFlags & KEYINFO_ORDER_BIGNULL ) break;
    }
    if( i==n){
      nOrderBy = n;
    }
  }

  /* Allocate the sqlite3_index_info structure
  */
  pIdxInfo = sqlite3DbMallocZero(pParse->db, sizeof(*pIdxInfo)
                           + (sizeof(*pIdxCons) + sizeof(*pUsage))*nTerm
                           + sizeof(*pIdxOrderBy)*nOrderBy + sizeof(*pHidden) );
  if( pIdxInfo==0 ){
    sqlite3ErrorMsg(pParse, "out of memory");
    return 0;
  }

  /* Initialize the structure.  The sqlite3_index_info structure contains
  ** many fields that are declared "const" to prevent xBestIndex from
  ** changing them.  We have to do some funky casting in order to
  ** initialize those fields.
  */
  pHidden = (struct HiddenIndexInfo*)&pIdxInfo[1];
  pIdxCons = (struct sqlite3_index_constraint*)&pHidden[1];
  pIdxOrderBy = (struct sqlite3_index_orderby*)&pIdxCons[nTerm];
  pUsage = (struct sqlite3_index_constraint_usage*)&pIdxOrderBy[nOrderBy];
  *(int*)&pIdxInfo->nConstraint = nTerm;
  *(int*)&pIdxInfo->nOrderBy = nOrderBy;
  *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint = pIdxCons;
  *(struct sqlite3_index_orderby**)&pIdxInfo->aOrderBy = pIdxOrderBy;
  *(struct sqlite3_index_constraint_usage**)&pIdxInfo->aConstraintUsage =
                                                                   pUsage;

  pHidden->pWC = pWC;
  pHidden->pParse = pParse;
  for(i=j=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
    u16 op;
    if( pTerm->leftCursor != pSrc->iCursor ) continue;
    if( pTerm->prereqRight & mUnusable ) continue;
    assert( IsPowerOfTwo(pTerm->eOperator & ~WO_EQUIV) );
    testcase( pTerm->eOperator & WO_IN );
    testcase( pTerm->eOperator & WO_IS );
    testcase( pTerm->eOperator & WO_ISNULL );
    testcase( pTerm->eOperator & WO_ALL );
    if( (pTerm->eOperator & ~(WO_EQUIV))==0 ) continue;
    if( pTerm->wtFlags & TERM_VNULL ) continue;
    if( (pSrc->fg.jointype & JT_LEFT)!=0
     && !ExprHasProperty(pTerm->pExpr, EP_FromJoin)
     && (pTerm->eOperator & (WO_IS|WO_ISNULL))
    ){
      /* An "IS" term in the WHERE clause where the virtual table is the rhs
      ** of a LEFT JOIN. Do not pass this term to the virtual table
      ** implementation, as this can lead to incorrect results from SQL such
      ** as:
      **
      **   "LEFT JOIN vtab WHERE vtab.col IS NULL"  */
      testcase( pTerm->eOperator & WO_ISNULL );
      testcase( pTerm->eOperator & WO_IS );
      continue;
    }
    assert( pTerm->u.leftColumn>=(-1) );
    pIdxCons[j].iColumn = pTerm->u.leftColumn;
    pIdxCons[j].iTermOffset = i;
    op = pTerm->eOperator & WO_ALL;
    if( op==WO_IN ) op = WO_EQ;
    if( op==WO_AUX ){
      pIdxCons[j].op = pTerm->eMatchOp;
    }else if( op & (WO_ISNULL|WO_IS) ){
      if( op==WO_ISNULL ){
        pIdxCons[j].op = SQLITE_INDEX_CONSTRAINT_ISNULL;
      }else{
        pIdxCons[j].op = SQLITE_INDEX_CONSTRAINT_IS;
      }
    }else{
      pIdxCons[j].op = (u8)op;
      /* The direct assignment in the previous line is possible only because
      ** the WO_ and SQLITE_INDEX_CONSTRAINT_ codes are identical.  The
      ** following asserts verify this fact. */
      assert( WO_EQ==SQLITE_INDEX_CONSTRAINT_EQ );
      assert( WO_LT==SQLITE_INDEX_CONSTRAINT_LT );
      assert( WO_LE==SQLITE_INDEX_CONSTRAINT_LE );
      assert( WO_GT==SQLITE_INDEX_CONSTRAINT_GT );
      assert( WO_GE==SQLITE_INDEX_CONSTRAINT_GE );
      assert( pTerm->eOperator&(WO_IN|WO_EQ|WO_LT|WO_LE|WO_GT|WO_GE|WO_AUX) );

      if( op & (WO_LT|WO_LE|WO_GT|WO_GE)
       && sqlite3ExprIsVector(pTerm->pExpr->pRight) 
      ){
        if( i<16 ) mNoOmit |= (1 << i);
        if( op==WO_LT ) pIdxCons[j].op = WO_LE;
        if( op==WO_GT ) pIdxCons[j].op = WO_GE;
      }
    }

    j++;
  }
  for(i=0; i<nOrderBy; i++){
    Expr *pExpr = pOrderBy->a[i].pExpr;
    pIdxOrderBy[i].iColumn = pExpr->iColumn;
    pIdxOrderBy[i].desc = pOrderBy->a[i].sortFlags & KEYINFO_ORDER_DESC;
  }

  *pmNoOmit = mNoOmit;
  return pIdxInfo;
}