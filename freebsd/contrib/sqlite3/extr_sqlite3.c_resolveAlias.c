#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int mallocFailed; } ;
typedef  TYPE_5__ sqlite3 ;
struct TYPE_31__ {TYPE_3__* pWin; } ;
struct TYPE_29__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_35__ {scalar_t__ op; int flags; TYPE_4__ y; TYPE_2__ u; } ;
struct TYPE_34__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_33__ {TYPE_5__* db; } ;
struct TYPE_30__ {TYPE_8__* pOwner; } ;
struct TYPE_28__ {TYPE_8__* pExpr; } ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ ExprList ;
typedef  TYPE_8__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Alias ; 
 int /*<<< orphan*/  EP_IntValue ; 
 int EP_MemToken ; 
 int EP_Reduced ; 
 int /*<<< orphan*/  EP_Static ; 
 int EP_TokenOnly ; 
 int /*<<< orphan*/  EP_WinFunc ; 
 scalar_t__ ExprHasProperty (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_COLLATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  incrAggFunctionDepth (TYPE_8__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3DbStrDup (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* sqlite3ExprAddCollateString (TYPE_6__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_5__*,TYPE_8__*) ; 
 TYPE_8__* sqlite3ExprDup (TYPE_5__*,TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resolveAlias(
  Parse *pParse,         /* Parsing context */
  ExprList *pEList,      /* A result set */
  int iCol,              /* A column in the result set.  0..pEList->nExpr-1 */
  Expr *pExpr,           /* Transform this into an alias to the result set */
  const char *zType,     /* "GROUP" or "ORDER" or "" */
  int nSubquery          /* Number of subqueries that the label is moving */
){
  Expr *pOrig;           /* The iCol-th column of the result set */
  Expr *pDup;            /* Copy of pOrig */
  sqlite3 *db;           /* The database connection */

  assert( iCol>=0 && iCol<pEList->nExpr );
  pOrig = pEList->a[iCol].pExpr;
  assert( pOrig!=0 );
  db = pParse->db;
  pDup = sqlite3ExprDup(db, pOrig, 0);
  if( pDup!=0 ){
    if( zType[0]!='G' ) incrAggFunctionDepth(pDup, nSubquery);
    if( pExpr->op==TK_COLLATE ){
      pDup = sqlite3ExprAddCollateString(pParse, pDup, pExpr->u.zToken);
    }

    /* Before calling sqlite3ExprDelete(), set the EP_Static flag. This 
    ** prevents ExprDelete() from deleting the Expr structure itself,
    ** allowing it to be repopulated by the memcpy() on the following line.
    ** The pExpr->u.zToken might point into memory that will be freed by the
    ** sqlite3DbFree(db, pDup) on the last line of this block, so be sure to
    ** make a copy of the token before doing the sqlite3DbFree().
    */
    ExprSetProperty(pExpr, EP_Static);
    sqlite3ExprDelete(db, pExpr);
    memcpy(pExpr, pDup, sizeof(*pExpr));
    if( !ExprHasProperty(pExpr, EP_IntValue) && pExpr->u.zToken!=0 ){
      assert( (pExpr->flags & (EP_Reduced|EP_TokenOnly))==0 );
      pExpr->u.zToken = sqlite3DbStrDup(db, pExpr->u.zToken);
      pExpr->flags |= EP_MemToken;
    }
    if( ExprHasProperty(pExpr, EP_WinFunc) ){
      if( pExpr->y.pWin!=0 ){
        pExpr->y.pWin->pOwner = pExpr;
      }else{
        assert( db->mallocFailed );
      }
    }
    sqlite3DbFree(db, pDup);
  }
  ExprSetProperty(pExpr, EP_Alias);
}