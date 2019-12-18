#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct SrcCount {int /*<<< orphan*/  nOther; int /*<<< orphan*/  nThis; TYPE_4__* pSrc; } ;
struct TYPE_8__ {struct SrcCount* pSrcCount; } ;
struct TYPE_10__ {TYPE_1__ u; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_12__ {scalar_t__ op; scalar_t__ iTable; } ;
struct TYPE_11__ {int nSrc; TYPE_2__* a; } ;
struct TYPE_9__ {scalar_t__ iCursor; } ;
typedef  TYPE_4__ SrcList ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 scalar_t__ TK_AGG_COLUMN ; 
 scalar_t__ TK_COLUMN ; 
 int WRC_Continue ; 

__attribute__((used)) static int exprSrcCount(Walker *pWalker, Expr *pExpr){
  /* The NEVER() on the second term is because sqlite3FunctionUsesThisSrc()
  ** is always called before sqlite3ExprAnalyzeAggregates() and so the
  ** TK_COLUMNs have not yet been converted into TK_AGG_COLUMN.  If
  ** sqlite3FunctionUsesThisSrc() is used differently in the future, the
  ** NEVER() will need to be removed. */
  if( pExpr->op==TK_COLUMN || NEVER(pExpr->op==TK_AGG_COLUMN) ){
    int i;
    struct SrcCount *p = pWalker->u.pSrcCount;
    SrcList *pSrc = p->pSrc;
    int nSrc = pSrc ? pSrc->nSrc : 0;
    for(i=0; i<nSrc; i++){
      if( pExpr->iTable==pSrc->a[i].iCursor ) break;
    }
    if( i<nSrc ){
      p->nThis++;
    }else if( nSrc==0 || pExpr->iTable<pSrc->a[0].iCursor ){
      /* In a well-formed parse tree (no name resolution errors),
      ** TK_COLUMN nodes with smaller Expr.iTable values are in an
      ** outer context.  Those are the only ones to count as "other" */
      p->nOther++;
    }
  }
  return WRC_Continue;
}