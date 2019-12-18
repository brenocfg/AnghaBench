#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* pDfltColl; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  size_t i16 ;
struct TYPE_17__ {size_t iPKey; TYPE_6__* aCol; } ;
typedef  TYPE_3__ Table ;
struct TYPE_20__ {char* zColl; int /*<<< orphan*/  affinity; } ;
struct TYPE_19__ {int iTable; int /*<<< orphan*/  affExpr; } ;
struct TYPE_18__ {TYPE_2__* db; } ;
struct TYPE_15__ {char* zName; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ Expr ;
typedef  TYPE_6__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_AFF_INTEGER ; 
 int /*<<< orphan*/  TK_REGISTER ; 
 TYPE_5__* sqlite3Expr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* sqlite3ExprAddCollateString (TYPE_4__*,TYPE_5__*,char const*) ; 

__attribute__((used)) static Expr *exprTableRegister(
  Parse *pParse,     /* Parsing and code generating context */
  Table *pTab,       /* The table whose content is at r[regBase]... */
  int regBase,       /* Contents of table pTab */
  i16 iCol           /* Which column of pTab is desired */
){
  Expr *pExpr;
  Column *pCol;
  const char *zColl;
  sqlite3 *db = pParse->db;

  pExpr = sqlite3Expr(db, TK_REGISTER, 0);
  if( pExpr ){
    if( iCol>=0 && iCol!=pTab->iPKey ){
      pCol = &pTab->aCol[iCol];
      pExpr->iTable = regBase + iCol + 1;
      pExpr->affExpr = pCol->affinity;
      zColl = pCol->zColl;
      if( zColl==0 ) zColl = db->pDfltColl->zName;
      pExpr = sqlite3ExprAddCollateString(pParse, pExpr, zColl);
    }else{
      pExpr->iTable = regBase;
      pExpr->affExpr = SQLITE_AFF_INTEGER;
    }
  }
  return pExpr;
}