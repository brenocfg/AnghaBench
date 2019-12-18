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
struct mrb_insn_data {int /*<<< orphan*/  insn; } ;
struct TYPE_3__ {size_t pc; size_t lastpc; int /*<<< orphan*/ * iseq; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  OP_NOP ; 
 struct mrb_insn_data mrb_decode_insn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mrb_insn_data
mrb_last_insn(codegen_scope *s)
{
  if (s->pc == s->lastpc) {
    struct mrb_insn_data data;

    data.insn = OP_NOP;
    return data;
  }
  return mrb_decode_insn(&s->iseq[s->lastpc]);
}