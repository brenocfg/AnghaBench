#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ Proto ;
typedef  int OpCode ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 int GETARG_B (int /*<<< orphan*/ ) ; 
 int GETARG_sBx (int /*<<< orphan*/ ) ; 
 int GET_OPCODE (int /*<<< orphan*/ ) ; 
#define  OP_CALL 133 
#define  OP_JMP 132 
#define  OP_LOADNIL 131 
#define  OP_TAILCALL 130 
#define  OP_TEST 129 
#define  OP_TFORCALL 128 
 int filterpc (int,int) ; 
 int /*<<< orphan*/  testAMode (int) ; 

__attribute__((used)) static int findsetreg (Proto *p, int lastpc, int reg) {
  int pc;
  int setreg = -1;  /* keep last instruction that changed 'reg' */
  int jmptarget = 0;  /* any code before this address is conditional */
  for (pc = 0; pc < lastpc; pc++) {
    Instruction i = p->code[pc];
    OpCode op = GET_OPCODE(i);
    int a = GETARG_A(i);
    switch (op) {
      case OP_LOADNIL: {
        int b = GETARG_B(i);
        if (a <= reg && reg <= a + b)  /* set registers from 'a' to 'a+b' */
          setreg = filterpc(pc, jmptarget);
        break;
      }
      case OP_TFORCALL: {
        if (reg >= a + 2)  /* affect all regs above its base */
          setreg = filterpc(pc, jmptarget);
        break;
      }
      case OP_CALL:
      case OP_TAILCALL: {
        if (reg >= a)  /* affect all registers above base */
          setreg = filterpc(pc, jmptarget);
        break;
      }
      case OP_JMP: {
        int b = GETARG_sBx(i);
        int dest = pc + 1 + b;
        /* jump is forward and do not skip `lastpc'? */
        if (pc < dest && dest <= lastpc) {
          if (dest > jmptarget)
            jmptarget = dest;  /* update 'jmptarget' */
        }
        break;
      }
      case OP_TEST: {
        if (reg == a)  /* jumped code can change 'a' */
          setreg = filterpc(pc, jmptarget);
        break;
      }
      default:
        if (testAMode(op) && reg == a)  /* any instruction that set A */
          setreg = filterpc(pc, jmptarget);
        break;
    }
  }
  return setreg;
}