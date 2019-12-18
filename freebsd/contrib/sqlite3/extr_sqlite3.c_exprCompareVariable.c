#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_8__ {int iColumn; } ;
struct TYPE_7__ {int /*<<< orphan*/  pReprepare; int /*<<< orphan*/  pVdbe; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_AFF_BLOB ; 
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ sqlite3MemCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ValueFromExpr (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * sqlite3VdbeGetBoundValue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetVarmask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exprCompareVariable(Parse *pParse, Expr *pVar, Expr *pExpr){
  int res = 0;
  int iVar;
  sqlite3_value *pL, *pR = 0;
  
  sqlite3ValueFromExpr(pParse->db, pExpr, SQLITE_UTF8, SQLITE_AFF_BLOB, &pR);
  if( pR ){
    iVar = pVar->iColumn;
    sqlite3VdbeSetVarmask(pParse->pVdbe, iVar);
    pL = sqlite3VdbeGetBoundValue(pParse->pReprepare, iVar, SQLITE_AFF_BLOB);
    if( pL ){
      if( sqlite3_value_type(pL)==SQLITE_TEXT ){
        sqlite3_value_text(pL); /* Make sure the encoding is UTF-8 */
      }
      res =  0==sqlite3MemCompare(pL, pR, 0);
    }
    sqlite3ValueFree(pR);
    sqlite3ValueFree(pL);
  }

  return res;
}