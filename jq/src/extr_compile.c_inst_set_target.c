#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int last; TYPE_2__* first; } ;
typedef  TYPE_3__ block ;
struct TYPE_11__ {int flags; } ;
struct TYPE_8__ {int target; } ;
struct TYPE_9__ {TYPE_1__ imm; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int OP_HAS_BRANCH ; 
 int /*<<< orphan*/  assert (int) ; 
 int block_is_single (TYPE_3__) ; 
 TYPE_4__* opcode_describe (int /*<<< orphan*/ ) ; 

void inst_set_target(block b, block target) {
  assert(block_is_single(b));
  assert(opcode_describe(b.first->op)->flags & OP_HAS_BRANCH);
  assert(target.last);
  b.first->imm.target = target.last;
}