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
typedef  int /*<<< orphan*/  opcode ;
struct TYPE_7__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;
struct TYPE_8__ {int flags; } ;
struct TYPE_6__ {struct TYPE_6__* bound_by; } ;

/* Variables and functions */
 int OP_HAS_VARIABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ gen_op_unbound (int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* opcode_describe (int /*<<< orphan*/ ) ; 

block gen_op_var_fresh(opcode op, const char* name) {
  assert(opcode_describe(op)->flags & OP_HAS_VARIABLE);
  block b = gen_op_unbound(op, name);
  b.first->bound_by = b.first;
  return b;
}