#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  regArg; int /*<<< orphan*/ * pVdbe; TYPE_2__* pMWin; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_1__ WindowCodeArg ;
struct TYPE_10__ {int csrApp; int iEphCsr; int regAccum; int regStartRowid; int regEndRowid; scalar_t__ eExclude; TYPE_8__* pOrderBy; struct TYPE_10__* pNextWin; } ;
typedef  TYPE_2__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_11__ {int nExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Eq ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_Gt ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_Rowid ; 
 int /*<<< orphan*/  OP_SeekGE ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 scalar_t__ TK_CURRENT ; 
 scalar_t__ TK_NO ; 
 scalar_t__ TK_TIES ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageEqNe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeModuleComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempRange (int /*<<< orphan*/ *,int) ; 
 int sqlite3GetTempReg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3KeyInfoFromExprList (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windowAggFinal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  windowAggStep (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowReadPeerValues (TYPE_1__*,int,int) ; 

__attribute__((used)) static void windowFullScan(WindowCodeArg *p){
  Window *pWin;
  Parse *pParse = p->pParse;
  Window *pMWin = p->pMWin;
  Vdbe *v = p->pVdbe;

  int regCRowid = 0;              /* Current rowid value */
  int regCPeer = 0;               /* Current peer values */
  int regRowid = 0;               /* AggStep rowid value */
  int regPeer = 0;                /* AggStep peer values */

  int nPeer;
  int lblNext;
  int lblBrk;
  int addrNext;
  int csr;

  VdbeModuleComment((v, "windowFullScan begin"));

  assert( pMWin!=0 );
  csr = pMWin->csrApp;
  nPeer = (pMWin->pOrderBy ? pMWin->pOrderBy->nExpr : 0);

  lblNext = sqlite3VdbeMakeLabel(pParse);
  lblBrk = sqlite3VdbeMakeLabel(pParse);

  regCRowid = sqlite3GetTempReg(pParse);
  regRowid = sqlite3GetTempReg(pParse);
  if( nPeer ){
    regCPeer = sqlite3GetTempRange(pParse, nPeer);
    regPeer = sqlite3GetTempRange(pParse, nPeer);
  }

  sqlite3VdbeAddOp2(v, OP_Rowid, pMWin->iEphCsr, regCRowid);
  windowReadPeerValues(p, pMWin->iEphCsr, regCPeer);

  for(pWin=pMWin; pWin; pWin=pWin->pNextWin){
    sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regAccum);
  }

  sqlite3VdbeAddOp3(v, OP_SeekGE, csr, lblBrk, pMWin->regStartRowid);
  VdbeCoverage(v);
  addrNext = sqlite3VdbeCurrentAddr(v);
  sqlite3VdbeAddOp2(v, OP_Rowid, csr, regRowid);
  sqlite3VdbeAddOp3(v, OP_Gt, pMWin->regEndRowid, lblBrk, regRowid);
  VdbeCoverageNeverNull(v);

  if( pMWin->eExclude==TK_CURRENT ){
    sqlite3VdbeAddOp3(v, OP_Eq, regCRowid, lblNext, regRowid);
    VdbeCoverageNeverNull(v);
  }else if( pMWin->eExclude!=TK_NO ){
    int addr;
    int addrEq = 0;
    KeyInfo *pKeyInfo = 0;

    if( pMWin->pOrderBy ){
      pKeyInfo = sqlite3KeyInfoFromExprList(pParse, pMWin->pOrderBy, 0, 0);
    }
    if( pMWin->eExclude==TK_TIES ){
      addrEq = sqlite3VdbeAddOp3(v, OP_Eq, regCRowid, 0, regRowid);
      VdbeCoverageNeverNull(v);
    }
    if( pKeyInfo ){
      windowReadPeerValues(p, csr, regPeer);
      sqlite3VdbeAddOp3(v, OP_Compare, regPeer, regCPeer, nPeer);
      sqlite3VdbeAppendP4(v, (void*)pKeyInfo, P4_KEYINFO);
      addr = sqlite3VdbeCurrentAddr(v)+1;
      sqlite3VdbeAddOp3(v, OP_Jump, addr, lblNext, addr);
      VdbeCoverageEqNe(v);
    }else{
      sqlite3VdbeAddOp2(v, OP_Goto, 0, lblNext);
    }
    if( addrEq ) sqlite3VdbeJumpHere(v, addrEq);
  }

  windowAggStep(p, pMWin, csr, 0, p->regArg);

  sqlite3VdbeResolveLabel(v, lblNext);
  sqlite3VdbeAddOp2(v, OP_Next, csr, addrNext);
  VdbeCoverage(v);
  sqlite3VdbeJumpHere(v, addrNext-1);
  sqlite3VdbeJumpHere(v, addrNext+1);
  sqlite3ReleaseTempReg(pParse, regRowid);
  sqlite3ReleaseTempReg(pParse, regCRowid);
  if( nPeer ){
    sqlite3ReleaseTempRange(pParse, regPeer, nPeer);
    sqlite3ReleaseTempRange(pParse, regCPeer, nPeer);
  }

  windowAggFinal(p, 1);
  VdbeModuleComment((v, "windowFullScan end"));
}