#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int csr; int reg; } ;
struct TYPE_15__ {int csr; int reg; } ;
struct TYPE_14__ {int csr; int reg; } ;
struct TYPE_17__ {int eDelete; int /*<<< orphan*/  regArg; TYPE_3__ end; TYPE_2__ start; TYPE_1__ current; int /*<<< orphan*/ * pVdbe; TYPE_5__* pMWin; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_4__ WindowCodeArg ;
struct TYPE_18__ {scalar_t__ eFrmType; scalar_t__ eStart; scalar_t__ regStartRowid; scalar_t__ eEnd; int regEndRowid; TYPE_8__* pOrderBy; } ;
typedef  TYPE_5__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_19__ {int nExpr; } ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OPFLAG_SAVEPOSITION ; 
 int /*<<< orphan*/  OP_AddImm ; 
 int /*<<< orphan*/  OP_Delete ; 
 int /*<<< orphan*/  OP_Ge ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_Gt ; 
 int /*<<< orphan*/  OP_IfPos ; 
 int /*<<< orphan*/  OP_Le ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Rowid ; 
 scalar_t__ TK_FOLLOWING ; 
 scalar_t__ TK_PRECEDING ; 
 scalar_t__ TK_RANGE ; 
 scalar_t__ TK_ROWS ; 
 scalar_t__ TK_UNBOUNDED ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
#define  WINDOW_AGGINVERSE 129 
 int WINDOW_AGGSTEP ; 
#define  WINDOW_RETURN_ROW 128 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempRange (int /*<<< orphan*/ *,int) ; 
 int sqlite3GetTempReg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windowAggFinal (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowAggStep (TYPE_4__*,TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowCodeRangeTest (TYPE_4__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  windowIfNewPeer (int /*<<< orphan*/ *,TYPE_8__*,int,int,int) ; 
 int /*<<< orphan*/  windowReadPeerValues (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  windowReturnOneRow (TYPE_4__*) ; 

__attribute__((used)) static int windowCodeOp(
 WindowCodeArg *p,                /* Context object */
 int op,                          /* WINDOW_RETURN_ROW, AGGSTEP or AGGINVERSE */
 int regCountdown,                /* Register for OP_IfPos countdown */
 int jumpOnEof                    /* Jump here if stepped cursor reaches EOF */
){
  int csr, reg;
  Parse *pParse = p->pParse;
  Window *pMWin = p->pMWin;
  int ret = 0;
  Vdbe *v = p->pVdbe;
  int addrContinue = 0;
  int bPeer = (pMWin->eFrmType!=TK_ROWS);

  int lblDone = sqlite3VdbeMakeLabel(pParse);
  int addrNextRange = 0;

  /* Special case - WINDOW_AGGINVERSE is always a no-op if the frame
  ** starts with UNBOUNDED PRECEDING. */
  if( op==WINDOW_AGGINVERSE && pMWin->eStart==TK_UNBOUNDED ){
    assert( regCountdown==0 && jumpOnEof==0 );
    return 0;
  }

  if( regCountdown>0 ){
    if( pMWin->eFrmType==TK_RANGE ){
      addrNextRange = sqlite3VdbeCurrentAddr(v);
      assert( op==WINDOW_AGGINVERSE || op==WINDOW_AGGSTEP );
      if( op==WINDOW_AGGINVERSE ){
        if( pMWin->eStart==TK_FOLLOWING ){
          windowCodeRangeTest(
              p, OP_Le, p->current.csr, regCountdown, p->start.csr, lblDone
          );
        }else{
          windowCodeRangeTest(
              p, OP_Ge, p->start.csr, regCountdown, p->current.csr, lblDone
          );
        }
      }else{
        windowCodeRangeTest(
            p, OP_Gt, p->end.csr, regCountdown, p->current.csr, lblDone
        );
      }
    }else{
      sqlite3VdbeAddOp3(v, OP_IfPos, regCountdown, lblDone, 1);
      VdbeCoverage(v);
    }
  }

  if( op==WINDOW_RETURN_ROW && pMWin->regStartRowid==0 ){
    windowAggFinal(p, 0);
  }
  addrContinue = sqlite3VdbeCurrentAddr(v);

  /* If this is a (RANGE BETWEEN a FOLLOWING AND b FOLLOWING) or
  ** (RANGE BETWEEN b PRECEDING AND a PRECEDING) frame, ensure the 
  ** start cursor does not advance past the end cursor within the 
  ** temporary table. It otherwise might, if (a>b).  */
  if( pMWin->eStart==pMWin->eEnd && regCountdown
   && pMWin->eFrmType==TK_RANGE && op==WINDOW_AGGINVERSE
  ){
    int regRowid1 = sqlite3GetTempReg(pParse);
    int regRowid2 = sqlite3GetTempReg(pParse);
    sqlite3VdbeAddOp2(v, OP_Rowid, p->start.csr, regRowid1);
    sqlite3VdbeAddOp2(v, OP_Rowid, p->end.csr, regRowid2);
    sqlite3VdbeAddOp3(v, OP_Ge, regRowid2, lblDone, regRowid1);
    VdbeCoverage(v);
    sqlite3ReleaseTempReg(pParse, regRowid1);
    sqlite3ReleaseTempReg(pParse, regRowid2);
    assert( pMWin->eStart==TK_PRECEDING || pMWin->eStart==TK_FOLLOWING );
  }

  switch( op ){
    case WINDOW_RETURN_ROW:
      csr = p->current.csr;
      reg = p->current.reg;
      windowReturnOneRow(p);
      break;

    case WINDOW_AGGINVERSE:
      csr = p->start.csr;
      reg = p->start.reg;
      if( pMWin->regStartRowid ){
        assert( pMWin->regEndRowid );
        sqlite3VdbeAddOp2(v, OP_AddImm, pMWin->regStartRowid, 1);
      }else{
        windowAggStep(p, pMWin, csr, 1, p->regArg);
      }
      break;

    default:
      assert( op==WINDOW_AGGSTEP );
      csr = p->end.csr;
      reg = p->end.reg;
      if( pMWin->regStartRowid ){
        assert( pMWin->regEndRowid );
        sqlite3VdbeAddOp2(v, OP_AddImm, pMWin->regEndRowid, 1);
      }else{
        windowAggStep(p, pMWin, csr, 0, p->regArg);
      }
      break;
  }

  if( op==p->eDelete ){
    sqlite3VdbeAddOp1(v, OP_Delete, csr);
    sqlite3VdbeChangeP5(v, OPFLAG_SAVEPOSITION);
  }

  if( jumpOnEof ){
    sqlite3VdbeAddOp2(v, OP_Next, csr, sqlite3VdbeCurrentAddr(v)+2);
    VdbeCoverage(v);
    ret = sqlite3VdbeAddOp0(v, OP_Goto);
  }else{
    sqlite3VdbeAddOp2(v, OP_Next, csr, sqlite3VdbeCurrentAddr(v)+1+bPeer);
    VdbeCoverage(v);
    if( bPeer ){
      sqlite3VdbeAddOp2(v, OP_Goto, 0, lblDone);
    }
  }

  if( bPeer ){
    int nReg = (pMWin->pOrderBy ? pMWin->pOrderBy->nExpr : 0);
    int regTmp = (nReg ? sqlite3GetTempRange(pParse, nReg) : 0);
    windowReadPeerValues(p, csr, regTmp);
    windowIfNewPeer(pParse, pMWin->pOrderBy, regTmp, reg, addrContinue);
    sqlite3ReleaseTempRange(pParse, regTmp, nReg);
  }

  if( addrNextRange ){
    sqlite3VdbeAddOp2(v, OP_Goto, 0, addrNextRange);
  }
  sqlite3VdbeResolveLabel(v, lblDone);
  return ret;
}