#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opcode ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  inst_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inst_new (int /*<<< orphan*/ ) ; 
 TYPE_1__* opcode_describe (int /*<<< orphan*/ ) ; 

block gen_op_simple(opcode op) {
  assert(opcode_describe(op)->length == 1);
  return inst_block(inst_new(op));
}