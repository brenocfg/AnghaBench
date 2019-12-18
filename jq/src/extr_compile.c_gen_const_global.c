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
struct TYPE_7__ {scalar_t__ any_unbound; int /*<<< orphan*/  symbol; TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int OP_HAS_BINDING ; 
 int OP_HAS_CONSTANT ; 
 int OP_HAS_VARIABLE ; 
 int /*<<< orphan*/  STORE_GLOBAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  inst_block (TYPE_2__*) ; 
 TYPE_2__* inst_new (int /*<<< orphan*/ ) ; 
 TYPE_3__* opcode_describe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

block gen_const_global(jv constant, const char *name) {
  assert((opcode_describe(STORE_GLOBAL)->flags & (OP_HAS_CONSTANT | OP_HAS_VARIABLE | OP_HAS_BINDING)) ==
         (OP_HAS_CONSTANT | OP_HAS_VARIABLE | OP_HAS_BINDING));
  inst* i = inst_new(STORE_GLOBAL);
  i->imm.constant = constant;
  i->symbol = strdup(name);
  i->any_unbound = 0;
  return inst_block(i);
}