#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_6__ {int /*<<< orphan*/  constant; } ;
struct TYPE_7__ {TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int OP_HAS_CONSTANT ; 
 int /*<<< orphan*/  PUSHK_UNDER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  inst_block (TYPE_2__*) ; 
 TYPE_2__* inst_new (int /*<<< orphan*/ ) ; 
 TYPE_3__* opcode_describe (int /*<<< orphan*/ ) ; 

block gen_op_pushk_under(jv constant) {
  assert(opcode_describe(PUSHK_UNDER)->flags & OP_HAS_CONSTANT);
  inst* i = inst_new(PUSHK_UNDER);
  i->imm.constant = constant;
  return inst_block(i);
}