#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mrb_insn_data {int insn; int b; } ;
struct TYPE_7__ {int /*<<< orphan*/  lastpc; int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_ADDI ; 
#define  OP_LOADI 137 
#define  OP_LOADI_0 136 
#define  OP_LOADI_1 135 
#define  OP_LOADI_2 134 
#define  OP_LOADI_3 133 
#define  OP_LOADI_4 132 
#define  OP_LOADI_5 131 
#define  OP_LOADI_6 130 
#define  OP_LOADI_7 129 
#define  OP_LOADI__1 128 
 int /*<<< orphan*/  OP_SUB ; 
 int /*<<< orphan*/  OP_SUBI ; 
 int /*<<< orphan*/  genop_1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mrb_insn_data mrb_last_insn (TYPE_1__*) ; 
 scalar_t__ no_peephole (TYPE_1__*) ; 

__attribute__((used)) static void
gen_addsub(codegen_scope *s, uint8_t op, uint16_t dst)
{
  if (no_peephole(s)) {
  normal:
    genop_1(s, op, dst);
    return;
  }
  else {
    struct mrb_insn_data data = mrb_last_insn(s);

    switch (data.insn) {
    case OP_LOADI__1:
      if (op == OP_ADD) op = OP_SUB;
      else op = OP_ADD;
      data.b = 1;
      goto replace;
    case OP_LOADI_0: case OP_LOADI_1: case OP_LOADI_2: case OP_LOADI_3:
    case OP_LOADI_4: case OP_LOADI_5: case OP_LOADI_6: case OP_LOADI_7:
      data.b = data.insn - OP_LOADI_0;
      /* fall through */
    case OP_LOADI:
    replace:
      if (data.b >= 128) goto normal;
      s->pc = s->lastpc;
      if (op == OP_ADD) {
        genop_2(s, OP_ADDI, dst, (uint8_t)data.b);
      }
      else {
        genop_2(s, OP_SUBI, dst, (uint8_t)data.b);
      }
      break;
    default:
      goto normal;
    }
  }
}