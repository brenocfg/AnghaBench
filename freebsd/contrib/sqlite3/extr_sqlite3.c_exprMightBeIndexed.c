#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* pList; } ;
struct TYPE_10__ {scalar_t__ op; int iTable; int iColumn; TYPE_3__ x; } ;
struct TYPE_8__ {TYPE_1__* a; } ;
struct TYPE_7__ {TYPE_4__* pExpr; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_4__ Expr ;
typedef  int Bitmask ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 scalar_t__ TK_COLUMN ; 
 int TK_GE ; 
 int TK_GT ; 
 int TK_IN ; 
 int TK_IS ; 
 int TK_ISNULL ; 
 int TK_LE ; 
 int TK_LT ; 
 scalar_t__ TK_VECTOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int exprMightBeIndexed2 (int /*<<< orphan*/ *,int,int*,TYPE_4__*) ; 

__attribute__((used)) static int exprMightBeIndexed(
  SrcList *pFrom,        /* The FROM clause */
  Bitmask mPrereq,       /* Bitmask of FROM clause terms referenced by pExpr */
  int *aiCurCol,         /* Write the referenced table cursor & column here */
  Expr *pExpr,           /* An operand of a comparison operator */
  int op                 /* The specific comparison operator */
){
  /* If this expression is a vector to the left or right of a 
  ** inequality constraint (>, <, >= or <=), perform the processing 
  ** on the first element of the vector.  */
  assert( TK_GT+1==TK_LE && TK_GT+2==TK_LT && TK_GT+3==TK_GE );
  assert( TK_IS<TK_GE && TK_ISNULL<TK_GE && TK_IN<TK_GE );
  assert( op<=TK_GE );
  if( pExpr->op==TK_VECTOR && (op>=TK_GT && ALWAYS(op<=TK_GE)) ){
    pExpr = pExpr->x.pList->a[0].pExpr;
  }

  if( pExpr->op==TK_COLUMN ){
    aiCurCol[0] = pExpr->iTable;
    aiCurCol[1] = pExpr->iColumn;
    return 1;
  }
  if( mPrereq==0 ) return 0;                 /* No table references */
  if( (mPrereq&(mPrereq-1))!=0 ) return 0;   /* Refs more than one table */
  return exprMightBeIndexed2(pFrom,mPrereq,aiCurCol,pExpr);
}