#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ op; int /*<<< orphan*/  pRight; int /*<<< orphan*/  pLeft; } ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 scalar_t__ ExprHasProperty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OptimizationEnabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_Transitive ; 
 scalar_t__ TK_EQ ; 
 scalar_t__ TK_IS ; 
 int /*<<< orphan*/ * sqlite3BinaryCompareCollSeq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char sqlite3ExprAffinity (int /*<<< orphan*/ ) ; 
 int sqlite3ExprCollSeqMatch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3IsBinary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3IsNumericAffinity (char) ; 

__attribute__((used)) static int termIsEquivalence(Parse *pParse, Expr *pExpr){
  char aff1, aff2;
  CollSeq *pColl;
  if( !OptimizationEnabled(pParse->db, SQLITE_Transitive) ) return 0;
  if( pExpr->op!=TK_EQ && pExpr->op!=TK_IS ) return 0;
  if( ExprHasProperty(pExpr, EP_FromJoin) ) return 0;
  aff1 = sqlite3ExprAffinity(pExpr->pLeft);
  aff2 = sqlite3ExprAffinity(pExpr->pRight);
  if( aff1!=aff2
   && (!sqlite3IsNumericAffinity(aff1) || !sqlite3IsNumericAffinity(aff2))
  ){
    return 0;
  }
  pColl = sqlite3BinaryCompareCollSeq(pParse, pExpr->pLeft, pExpr->pRight);
  if( sqlite3IsBinary(pColl) ) return 1;
  return sqlite3ExprCollSeqMatch(pParse, pExpr->pLeft, pExpr->pRight);
}