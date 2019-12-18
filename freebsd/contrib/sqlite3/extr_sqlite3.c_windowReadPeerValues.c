#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pParse; TYPE_2__* pMWin; } ;
typedef  TYPE_1__ WindowCodeArg ;
struct TYPE_6__ {int nBufferCol; TYPE_3__* pPartition; TYPE_3__* pOrderBy; } ;
typedef  TYPE_2__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_7__ {int nExpr; } ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void windowReadPeerValues(
  WindowCodeArg *p,
  int csr,
  int reg
){
  Window *pMWin = p->pMWin;
  ExprList *pOrderBy = pMWin->pOrderBy;
  if( pOrderBy ){
    Vdbe *v = sqlite3GetVdbe(p->pParse);
    ExprList *pPart = pMWin->pPartition;
    int iColOff = pMWin->nBufferCol + (pPart ? pPart->nExpr : 0);
    int i;
    for(i=0; i<pOrderBy->nExpr; i++){
      sqlite3VdbeAddOp3(v, OP_Column, csr, iColOff+i, reg+i);
    }
  }
}