#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_17__ {int /*<<< orphan*/  nErr; TYPE_1__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_16__ {int iLimit; int /*<<< orphan*/  iOffset; } ;
struct TYPE_15__ {int iSdst; int nSdst; int eDest; int iSDParm; char* zAffSdst; } ;
struct TYPE_14__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_2__ SelectDest ;
typedef  TYPE_3__ Select ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  OPFLAG_APPEND ; 
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_DecrJumpZero ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_ResultRow ; 
 int /*<<< orphan*/  OP_Return ; 
 int /*<<< orphan*/  OP_Yield ; 
 int P4_KEYINFO ; 
#define  SRT_Coroutine 131 
#define  SRT_EphemTab 130 
 int SRT_Exists ; 
#define  SRT_Mem 129 
 int SRT_Output ; 
#define  SRT_Set 128 
 int SRT_Table ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeOffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeMove (TYPE_4__*,int,int,int) ; 
 int sqlite3GetTempRange (TYPE_4__*,int) ; 
 int sqlite3GetTempReg (TYPE_4__*) ; 
 scalar_t__ sqlite3KeyInfoRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_4__*,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int generateOutputSubroutine(
  Parse *pParse,          /* Parsing context */
  Select *p,              /* The SELECT statement */
  SelectDest *pIn,        /* Coroutine supplying data */
  SelectDest *pDest,      /* Where to send the data */
  int regReturn,          /* The return address register */
  int regPrev,            /* Previous result register.  No uniqueness if 0 */
  KeyInfo *pKeyInfo,      /* For comparing with previous entry */
  int iBreak              /* Jump here if we hit the LIMIT */
){
  Vdbe *v = pParse->pVdbe;
  int iContinue;
  int addr;

  addr = sqlite3VdbeCurrentAddr(v);
  iContinue = sqlite3VdbeMakeLabel(pParse);

  /* Suppress duplicates for UNION, EXCEPT, and INTERSECT 
  */
  if( regPrev ){
    int addr1, addr2;
    addr1 = sqlite3VdbeAddOp1(v, OP_IfNot, regPrev); VdbeCoverage(v);
    addr2 = sqlite3VdbeAddOp4(v, OP_Compare, pIn->iSdst, regPrev+1, pIn->nSdst,
                              (char*)sqlite3KeyInfoRef(pKeyInfo), P4_KEYINFO);
    sqlite3VdbeAddOp3(v, OP_Jump, addr2+2, iContinue, addr2+2); VdbeCoverage(v);
    sqlite3VdbeJumpHere(v, addr1);
    sqlite3VdbeAddOp3(v, OP_Copy, pIn->iSdst, regPrev+1, pIn->nSdst-1);
    sqlite3VdbeAddOp2(v, OP_Integer, 1, regPrev);
  }
  if( pParse->db->mallocFailed ) return 0;

  /* Suppress the first OFFSET entries if there is an OFFSET clause
  */
  codeOffset(v, p->iOffset, iContinue);

  assert( pDest->eDest!=SRT_Exists );
  assert( pDest->eDest!=SRT_Table );
  switch( pDest->eDest ){
    /* Store the result as data using a unique key.
    */
    case SRT_EphemTab: {
      int r1 = sqlite3GetTempReg(pParse);
      int r2 = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp3(v, OP_MakeRecord, pIn->iSdst, pIn->nSdst, r1);
      sqlite3VdbeAddOp2(v, OP_NewRowid, pDest->iSDParm, r2);
      sqlite3VdbeAddOp3(v, OP_Insert, pDest->iSDParm, r1, r2);
      sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
      sqlite3ReleaseTempReg(pParse, r2);
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }

#ifndef SQLITE_OMIT_SUBQUERY
    /* If we are creating a set for an "expr IN (SELECT ...)".
    */
    case SRT_Set: {
      int r1;
      testcase( pIn->nSdst>1 );
      r1 = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp4(v, OP_MakeRecord, pIn->iSdst, pIn->nSdst, 
          r1, pDest->zAffSdst, pIn->nSdst);
      sqlite3VdbeAddOp4Int(v, OP_IdxInsert, pDest->iSDParm, r1,
                           pIn->iSdst, pIn->nSdst);
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }

    /* If this is a scalar select that is part of an expression, then
    ** store the results in the appropriate memory cell and break out
    ** of the scan loop.  Note that the select might return multiple columns
    ** if it is the RHS of a row-value IN operator.
    */
    case SRT_Mem: {
      if( pParse->nErr==0 ){
        testcase( pIn->nSdst>1 );
        sqlite3ExprCodeMove(pParse, pIn->iSdst, pDest->iSDParm, pIn->nSdst);
      }
      /* The LIMIT clause will jump out of the loop for us */
      break;
    }
#endif /* #ifndef SQLITE_OMIT_SUBQUERY */

    /* The results are stored in a sequence of registers
    ** starting at pDest->iSdst.  Then the co-routine yields.
    */
    case SRT_Coroutine: {
      if( pDest->iSdst==0 ){
        pDest->iSdst = sqlite3GetTempRange(pParse, pIn->nSdst);
        pDest->nSdst = pIn->nSdst;
      }
      sqlite3ExprCodeMove(pParse, pIn->iSdst, pDest->iSdst, pIn->nSdst);
      sqlite3VdbeAddOp1(v, OP_Yield, pDest->iSDParm);
      break;
    }

    /* If none of the above, then the result destination must be
    ** SRT_Output.  This routine is never called with any other
    ** destination other than the ones handled above or SRT_Output.
    **
    ** For SRT_Output, results are stored in a sequence of registers.  
    ** Then the OP_ResultRow opcode is used to cause sqlite3_step() to
    ** return the next row of result.
    */
    default: {
      assert( pDest->eDest==SRT_Output );
      sqlite3VdbeAddOp2(v, OP_ResultRow, pIn->iSdst, pIn->nSdst);
      break;
    }
  }

  /* Jump to the end of the loop if the LIMIT is reached.
  */
  if( p->iLimit ){
    sqlite3VdbeAddOp2(v, OP_DecrJumpZero, p->iLimit, iBreak); VdbeCoverage(v);
  }

  /* Generate the subroutine return
  */
  sqlite3VdbeResolveLabel(v, iContinue);
  sqlite3VdbeAddOp1(v, OP_Return, regReturn);

  return addr;
}