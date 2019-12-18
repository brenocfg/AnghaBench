#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int ArraySize (char const**) ; 
 int OE_Abort ; 
#define  OP_Ge 129 
#define  OP_Gt 128 
 int /*<<< orphan*/  OP_Halt ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_MustBeInt ; 
 int /*<<< orphan*/  OP_String8 ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int SQLITE_AFF_NUMERIC ; 
 int SQLITE_ERROR ; 
 int SQLITE_JUMPIFNULL ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VdbeCoverageNeverNullIf (int /*<<< orphan*/ *,int) ; 
 int WINDOW_STARTING_NUM ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempReg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3MayAbort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int const,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void windowCheckValue(Parse *pParse, int reg, int eCond){
  static const char *azErr[] = {
    "frame starting offset must be a non-negative integer",
    "frame ending offset must be a non-negative integer",
    "second argument to nth_value must be a positive integer",
    "frame starting offset must be a non-negative number",
    "frame ending offset must be a non-negative number",
  };
  static int aOp[] = { OP_Ge, OP_Ge, OP_Gt, OP_Ge, OP_Ge };
  Vdbe *v = sqlite3GetVdbe(pParse);
  int regZero = sqlite3GetTempReg(pParse);
  assert( eCond>=0 && eCond<ArraySize(azErr) );
  sqlite3VdbeAddOp2(v, OP_Integer, 0, regZero);
  if( eCond>=WINDOW_STARTING_NUM ){
    int regString = sqlite3GetTempReg(pParse);
    sqlite3VdbeAddOp4(v, OP_String8, 0, regString, 0, "", P4_STATIC);
    sqlite3VdbeAddOp3(v, OP_Ge, regString, sqlite3VdbeCurrentAddr(v)+2, reg);
    sqlite3VdbeChangeP5(v, SQLITE_AFF_NUMERIC|SQLITE_JUMPIFNULL);
    VdbeCoverage(v);
    assert( eCond==3 || eCond==4 );
    VdbeCoverageIf(v, eCond==3);
    VdbeCoverageIf(v, eCond==4);
  }else{
    sqlite3VdbeAddOp2(v, OP_MustBeInt, reg, sqlite3VdbeCurrentAddr(v)+2);
    VdbeCoverage(v);
    assert( eCond==0 || eCond==1 || eCond==2 );
    VdbeCoverageIf(v, eCond==0);
    VdbeCoverageIf(v, eCond==1);
    VdbeCoverageIf(v, eCond==2);
  }
  sqlite3VdbeAddOp3(v, aOp[eCond], regZero, sqlite3VdbeCurrentAddr(v)+2, reg);
  VdbeCoverageNeverNullIf(v, eCond==0); /* NULL case captured by */
  VdbeCoverageNeverNullIf(v, eCond==1); /*   the OP_MustBeInt */
  VdbeCoverageNeverNullIf(v, eCond==2);
  VdbeCoverageNeverNullIf(v, eCond==3); /* NULL case caught by */
  VdbeCoverageNeverNullIf(v, eCond==4); /*   the OP_Ge */
  sqlite3MayAbort(pParse);
  sqlite3VdbeAddOp2(v, OP_Halt, SQLITE_ERROR, OE_Abort);
  sqlite3VdbeAppendP4(v, (void*)azErr[eCond], P4_STATIC);
  sqlite3ReleaseTempReg(pParse, regZero);
}