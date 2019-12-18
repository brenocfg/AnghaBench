#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct opcode_obj_rewrite {int /*<<< orphan*/  (* update ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct opcode_obj_rewrite* find_op_rw (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
update_opcode_kidx(ipfw_insn *cmd, uint16_t idx)
{
	struct opcode_obj_rewrite *rw;

	rw = find_op_rw(cmd, NULL, NULL);
	KASSERT(rw != NULL, ("No handler to update opcode %d", cmd->opcode));
	rw->update(cmd, idx);
}