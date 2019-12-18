#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  pVdbe; } ;
typedef  TYPE_1__ Parse ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  P4_COLLSEQ ; 
 int binaryCompareP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3BinaryCompareCollSeq (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3VdbeAddOp4 (int /*<<< orphan*/ ,int,int,int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int codeCompare(
  Parse *pParse,    /* The parsing (and code generating) context */
  Expr *pLeft,      /* The left operand */
  Expr *pRight,     /* The right operand */
  int opcode,       /* The comparison opcode */
  int in1, int in2, /* Register holding operands */
  int dest,         /* Jump here if true.  */
  int jumpIfNull    /* If true, jump if either operand is NULL */
){
  int p5;
  int addr;
  CollSeq *p4;

  p4 = sqlite3BinaryCompareCollSeq(pParse, pLeft, pRight);
  p5 = binaryCompareP5(pLeft, pRight, jumpIfNull);
  addr = sqlite3VdbeAddOp4(pParse->pVdbe, opcode, in2, dest, in1,
                           (void*)p4, P4_COLLSEQ);
  sqlite3VdbeChangeP5(pParse->pVdbe, (u8)p5);
  return addr;
}