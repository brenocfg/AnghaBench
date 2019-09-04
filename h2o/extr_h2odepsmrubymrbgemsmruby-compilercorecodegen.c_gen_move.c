#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct mrb_insn_data {int insn; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_9__ {int /*<<< orphan*/  lastpc; int /*<<< orphan*/  pc; int /*<<< orphan*/  nlocals; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
#define  OP_BLKPUSH 155 
#define  OP_BLOCK 154 
#define  OP_GETCONST 153 
#define  OP_GETCV 152 
#define  OP_GETGV 151 
#define  OP_GETIV 150 
#define  OP_GETSV 149 
#define  OP_LAMBDA 148 
#define  OP_LOADF 147 
#define  OP_LOADI 146 
#define  OP_LOADINEG 145 
#define  OP_LOADI_0 144 
#define  OP_LOADI_1 143 
#define  OP_LOADI_2 142 
#define  OP_LOADI_3 141 
#define  OP_LOADI_4 140 
#define  OP_LOADI_5 139 
#define  OP_LOADI_6 138 
#define  OP_LOADI_7 137 
#define  OP_LOADI__1 136 
#define  OP_LOADL 135 
#define  OP_LOADNIL 134 
#define  OP_LOADSELF 133 
#define  OP_LOADSYM 132 
#define  OP_LOADT 131 
#define  OP_METHOD 130 
#define  OP_MOVE 129 
 int /*<<< orphan*/  OP_NOP ; 
#define  OP_STRING 128 
 int /*<<< orphan*/  genop_0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mrb_insn_data mrb_last_insn (TYPE_1__*) ; 
 scalar_t__ no_peephole (TYPE_1__*) ; 
 scalar_t__ on_eval (TYPE_1__*) ; 

__attribute__((used)) static void
gen_move(codegen_scope *s, uint16_t dst, uint16_t src, int nopeep)
{
  if (no_peephole(s)) {
  normal:
    genop_2(s, OP_MOVE, dst, src);
    if (on_eval(s)) {
      genop_0(s, OP_NOP);
    }
    return;
  }
  else {
    struct mrb_insn_data data = mrb_last_insn(s);

    switch (data.insn) {
    case OP_MOVE:
      if (dst == src) return;             /* remove useless MOVE */
      if (data.b == dst && data.a == src) /* skip swapping MOVE */
        return;
      goto normal;
    case OP_LOADNIL: case OP_LOADSELF: case OP_LOADT: case OP_LOADF:
    case OP_LOADI__1:
    case OP_LOADI_0: case OP_LOADI_1: case OP_LOADI_2: case OP_LOADI_3:
    case OP_LOADI_4: case OP_LOADI_5: case OP_LOADI_6: case OP_LOADI_7:
      if (nopeep || data.a != src || data.a < s->nlocals) goto normal;
      s->pc = s->lastpc;
      genop_1(s, data.insn, dst);
      break;
    case OP_LOADI: case OP_LOADINEG: case OP_LOADL: case OP_LOADSYM:
    case OP_GETGV: case OP_GETSV: case OP_GETIV: case OP_GETCV:
    case OP_GETCONST: case OP_STRING:
    case OP_LAMBDA: case OP_BLOCK: case OP_METHOD: case OP_BLKPUSH:
      if (nopeep || data.a != src || data.a < s->nlocals) goto normal;
      s->pc = s->lastpc;
      genop_2(s, data.insn, dst, data.b);
      break;
    default:
      goto normal;
    }
  }
}